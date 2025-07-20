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
class scan_result {
private:
    std::tuple<Ts...> values_;

public:
    const std::tuple<Ts...> &values() const { return values_; }
};

} // namespace stdx::details
