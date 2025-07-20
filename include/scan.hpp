#pragma once

#include "parse.hpp"
#include "types.hpp"

namespace stdx {

template <typename... Ts>
std::expected<details::scan_result<Ts...>, details::scan_error> scan(std::string_view input, std::string_view format) {
    auto sources = details::parse_sources(input, format);
    if (!sources) {
        return std::unexpected(sources.error());
    }

    auto &[format_parts, input_parts] = *sources;
    if (format_parts.size() != sizeof...(Ts)) {
        return std::unexpected(details::scan_error{"Argument count mismatch"});
    }

    std::tuple<Ts...> result;
    size_t index = 0;

    auto parse_element = [&](auto &value) -> bool {
        auto parsed = details::parse_value_with_format<std::remove_reference_t<decltype(value)>>(input_parts[index],
                                                                                                 format_parts[index]);
        if (!parsed) {
            return false;
        }
        value = std::move(*parsed);
        index++;
        return true;
    };

    if (!std::apply([&](auto &...args) { return (parse_element(args) && ...); }, result)) {
        return std::unexpected(details::scan_error{"Parsing failed"});
    }

    return details::scan_result<Ts...>{std::move(result)};
}

} // namespace stdx