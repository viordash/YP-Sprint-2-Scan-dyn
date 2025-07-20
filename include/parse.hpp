#pragma once

#include <array>
#include <charconv>
#include <cstdint>
#include <expected>
#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "types.hpp"

namespace stdx::details {

template <typename T, typename... Ts>
concept is_string_view_v = std::is_same_v<std::remove_cv_t<T>, std::string_view>;

template <typename T>
concept is_string_v = std::is_same_v<std::remove_cv_t<T>, std::string>;

// clang-format off
template <typename T>
concept is_supported_type_v = 
    std::is_same_v<std::remove_cv_t<T>, int8_t>  
    || std::is_same_v<std::remove_cv_t<T>, int16_t> 
    || std::is_same_v<std::remove_cv_t<T>, int32_t> 
    || std::is_same_v<std::remove_cv_t<T>, int64_t> 
    || std::is_same_v<std::remove_cv_t<T>, uint8_t> 
    || std::is_same_v<std::remove_cv_t<T>, uint16_t> 
    || std::is_same_v<std::remove_cv_t<T>, uint32_t> 
    || std::is_same_v<std::remove_cv_t<T>, uint64_t> 
    || std::is_same_v<std::remove_cv_t<T>, float>   
    || std::is_same_v<std::remove_cv_t<T>, double>  
    || is_string_view_v<T> 
    || is_string_v<T>;
// clang-format on

template <typename T>
static bool validate_format_specifier(std::string_view fmt) {
    if (fmt.empty()) {
        return true;
    }
    if (fmt.size() != 2) {
        return false;
    }

    if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
        return fmt == "%d";
    }
    if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>) {
        return fmt == "%u";
    }
    if constexpr (std::is_floating_point_v<T>) {
        return fmt == "%f";
    }
    if constexpr (is_string_view_v<T>) {
        return fmt == "%s";
    }
    if constexpr (is_string_v<T>) {
        return fmt == "%s";
    }
    return false;
}

template <typename T>
    requires is_supported_type_v<T>
std::expected<T, scan_error> parse_value_with_format(std::string_view input, std::string_view fmt) {
    if (!validate_format_specifier<T>(fmt)) {
        return std::unexpected(scan_error{"Invalid format specifier"});
    }

    if constexpr (is_string_view_v<T>) {
        return T(input);
    } else if constexpr (is_string_v<T>) {
        return T(input);
    } else {

        if (input.empty()) {
            return std::unexpected(scan_error{"Empty input"});
        }

        T value;
        auto result = std::from_chars(input.data(), input.data() + input.size(), value);
        if (result.ec == std::errc::result_out_of_range) {
            return std::unexpected(scan_error{"Conversion out of range"});
        } else if (result.ec != std::errc()) {
            return std::unexpected(scan_error{"Conversion failed"});
        }

        return value;
    }
}

// Функция для проверки корректности входных данных и выделения из обеих строк интересующих данных для парсинга
template <typename... Ts>
std::expected<std::pair<std::vector<std::string_view>, std::vector<std::string_view>>, scan_error>
parse_sources(std::string_view input, std::string_view format) {
    std::vector<std::string_view> format_parts; // Части формата между {}
    std::vector<std::string_view> input_parts;
    size_t start = 0;
    while (true) {
        size_t open = format.find('{', start);
        if (open == std::string_view::npos) {
            break;
        }
        size_t close = format.find('}', open);
        if (close == std::string_view::npos) {
            break;
        }

        // Если между предыдущей } и текущей { есть текст,
        // проверяем его наличие во входной строке
        if (open > start) {
            std::string_view between = format.substr(start, open - start);
            auto pos = input.find(between);
            if (input.size() < between.size() || pos == std::string_view::npos) {
                return std::unexpected(scan_error{"Unformatted text in input and format string are different"});
            }
            if (start != 0) {
                input_parts.emplace_back(input.substr(0, pos));
            }

            input = input.substr(pos + between.size());
        }

        // Сохраняем спецификатор формата (то, что между {})
        format_parts.push_back(format.substr(open + 1, close - open - 1));
        start = close + 1;
    }

    // Проверяем оставшийся текст после последней }
    if (start < format.size()) {
        std::string_view remaining_format = format.substr(start);
        auto pos = input.find(remaining_format);
        if (input.size() < remaining_format.size() || pos == std::string_view::npos) {
            return std::unexpected(scan_error{"Unformatted text in input and format string are different"});
        }
        input_parts.emplace_back(input.substr(0, pos));
        input = input.substr(pos + remaining_format.size());
    } else {
        input_parts.emplace_back(input);
    }
    return std::pair{format_parts, input_parts};
}

} // namespace stdx::details