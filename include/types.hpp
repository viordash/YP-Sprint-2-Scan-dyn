#pragma once
#include <string>
#include <tuple>

namespace stdx::details {

// Класс для хранения ошибки неуспешного сканирования

struct scan_error {
    std::string message;
};

// Шаблонный класс для хранения результатов успешного сканирования

template <typename... Ts>
struct scan_result {
    std::tuple<Ts...> values;
    explicit scan_result(std::tuple<Ts...> v) : values(std::move(v)) {}
};

} // namespace stdx::details
