#pragma once

#include "parse.hpp"
#include "types.hpp"

namespace stdx {

using namespace details;

template <typename... Ts>
std::expected<scan_result<Ts...>, scan_error> scan(std::string_view input, std::string_view format) {
    auto sources = parse_sources(input, format);
    if (!sources) {
        return std::unexpected(sources.error());
    }

    auto &[format_parts, input_parts] = *sources;
    if (format_parts.size() != sizeof...(Ts)) {
        return std::unexpected(scan_error{"Argument count mismatch"});
    }

    std::tuple<Ts...> result;
    size_t index = 0;

    auto parse_value = [&](auto &value) -> std::expected<void, scan_error> {
        auto parsed =
            parse_value_with_format<std::remove_reference_t<decltype(value)>>(input_parts[index], format_parts[index]);

        if (!parsed) {
            return std::unexpected(parsed.error());
        }

        value = std::move(*parsed);
        index++;
        return {};
    };

    auto parse_values = [&](auto &...args) -> std::expected<void, scan_error> {
        std::expected<void, scan_error> res = {};
        ((res = parse_value(args)) && ...);
        return res;
    };

    auto parse_res = std::apply(parse_values, result);
    if (!parse_res) {
        return std::unexpected(parse_res.error());
    }

    return scan_result<Ts...>{std::move(result)};
}

} // namespace stdx