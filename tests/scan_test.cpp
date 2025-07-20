#include <cstdint>
#include <gtest/gtest.h>
#include <print>

#include "scan.hpp"

using namespace stdx::details;

TEST(ScanTest, test_is_supported_type_v) {
    ASSERT_TRUE(is_supported_type_v<int8_t>);
    ASSERT_TRUE(is_supported_type_v<int16_t>);
    ASSERT_TRUE(is_supported_type_v<int32_t>);
    ASSERT_TRUE(is_supported_type_v<int64_t>);
    ASSERT_TRUE(is_supported_type_v<uint8_t>);
    ASSERT_TRUE(is_supported_type_v<uint16_t>);
    ASSERT_TRUE(is_supported_type_v<uint32_t>);
    ASSERT_TRUE(is_supported_type_v<uint64_t>);
    ASSERT_TRUE(is_supported_type_v<float>);
    ASSERT_TRUE(is_supported_type_v<double>);
    ASSERT_TRUE(is_supported_type_v<std::string_view>);
    ASSERT_TRUE(is_supported_type_v<std::string>);

    ASSERT_TRUE(is_supported_type_v<const int8_t>);
    ASSERT_TRUE(is_supported_type_v<const int16_t>);
    ASSERT_TRUE(is_supported_type_v<const int32_t>);
    ASSERT_TRUE(is_supported_type_v<const int64_t>);
    ASSERT_TRUE(is_supported_type_v<const uint8_t>);
    ASSERT_TRUE(is_supported_type_v<const uint16_t>);
    ASSERT_TRUE(is_supported_type_v<const uint32_t>);
    ASSERT_TRUE(is_supported_type_v<const uint64_t>);
    ASSERT_TRUE(is_supported_type_v<const float>);
    ASSERT_TRUE(is_supported_type_v<const double>);
    ASSERT_TRUE(is_supported_type_v<const std::string_view>);
    ASSERT_TRUE(is_supported_type_v<const std::string>);

    ASSERT_FALSE(is_supported_type_v<char>);
    ASSERT_FALSE(is_supported_type_v<void *>);

    ASSERT_FALSE(is_supported_type_v<const char>);
    ASSERT_FALSE(is_supported_type_v<const void *>);
}


TEST(ScanTest, SimpleTest) {
    auto result = stdx::scan<std::string>("number", "{}");
    ASSERT_FALSE(result);
}