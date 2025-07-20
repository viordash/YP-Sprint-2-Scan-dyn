#include <climits>
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

TEST(ScanTest, parse_value_with_format__invalid_specifier__returns_error) {
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "x").error().message, "Invalid format specifier");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "%x").error().message, "Invalid format specifier");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", " d").error().message, "Invalid format specifier");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "d").error().message, "Invalid format specifier");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "u").error().message, "Invalid format specifier");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "f").error().message, "Invalid format specifier");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "s").error().message, "Invalid format specifier");
}

TEST(ScanTest, parse_value_with_format__with_empty_input_in_numbers_returns_error) {
    ASSERT_EQ(parse_value_with_format<int8_t>("", "%d").error().message, "Empty input");
    ASSERT_EQ(parse_value_with_format<int16_t>("", "%d").error().message, "Empty input");
    ASSERT_EQ(parse_value_with_format<int32_t>("", "%d").error().message, "Empty input");
    ASSERT_EQ(parse_value_with_format<int64_t>("", "%d").error().message, "Empty input");

    ASSERT_EQ(parse_value_with_format<uint8_t>("", "%u").error().message, "Empty input");
    ASSERT_EQ(parse_value_with_format<uint16_t>("", "%u").error().message, "Empty input");
    ASSERT_EQ(parse_value_with_format<uint32_t>("", "%u").error().message, "Empty input");
    ASSERT_EQ(parse_value_with_format<uint64_t>("", "%u").error().message, "Empty input");

    ASSERT_EQ(parse_value_with_format<float>("", "%f").error().message, "Empty input");
    ASSERT_EQ(parse_value_with_format<double>("", "%f").error().message, "Empty input");
}

TEST(ScanTest, parse_value_with_format__int8_t) {
    ASSERT_EQ(parse_value_with_format<int8_t>("127", "%d"), std::numeric_limits<int8_t>::max());
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "%d"), 0);
    ASSERT_EQ(parse_value_with_format<int8_t>("-128", "%d"), std::numeric_limits<int8_t>::min());

    ASSERT_EQ(parse_value_with_format<int8_t>("128", "%d").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int8_t>("-129", "%d").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int8_t>("-", "%d").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<int8_t>("x", "%d").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__int8_t__without_specifier) {
    ASSERT_EQ(parse_value_with_format<int8_t>("127", ""), std::numeric_limits<int8_t>::max());
    ASSERT_EQ(parse_value_with_format<int8_t>("0", ""), 0);
    ASSERT_EQ(parse_value_with_format<int8_t>("-128", ""), std::numeric_limits<int8_t>::min());

    ASSERT_EQ(parse_value_with_format<int8_t>("128", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int8_t>("-129", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int8_t>("-", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<int8_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__int16_t) {
    ASSERT_EQ(parse_value_with_format<int16_t>("32767", "%d"), std::numeric_limits<int16_t>::max());
    ASSERT_EQ(parse_value_with_format<int16_t>("0", "%d"), 0);
    ASSERT_EQ(parse_value_with_format<int16_t>("-32768", "%d"), std::numeric_limits<int16_t>::min());

    ASSERT_EQ(parse_value_with_format<int16_t>("32768", "%d").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int16_t>("-32769", "%d").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int16_t>("-", "%d").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<int16_t>("x", "%d").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__int16_t__without_specifier) {
    ASSERT_EQ(parse_value_with_format<int16_t>("32767", ""), std::numeric_limits<int16_t>::max());
    ASSERT_EQ(parse_value_with_format<int16_t>("0", ""), 0);
    ASSERT_EQ(parse_value_with_format<int16_t>("-32768", ""), std::numeric_limits<int16_t>::min());

    ASSERT_EQ(parse_value_with_format<int16_t>("32768", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int16_t>("-32769", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int16_t>("-", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<int16_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__int32_t) {
    ASSERT_EQ(parse_value_with_format<int32_t>("2147483647", "%d"), std::numeric_limits<int32_t>::max());
    ASSERT_EQ(parse_value_with_format<int32_t>("0", "%d"), 0);
    ASSERT_EQ(parse_value_with_format<int32_t>("-2147483648", "%d"), std::numeric_limits<int32_t>::min());

    ASSERT_EQ(parse_value_with_format<int32_t>("2147483648", "%d").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int32_t>("-2147483649", "%d").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int32_t>("-", "%d").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<int32_t>("x", "%d").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__int32_t__without_specifier) {
    ASSERT_EQ(parse_value_with_format<int32_t>("2147483647", ""), std::numeric_limits<int32_t>::max());
    ASSERT_EQ(parse_value_with_format<int32_t>("0", ""), 0);
    ASSERT_EQ(parse_value_with_format<int32_t>("-2147483648", ""), std::numeric_limits<int32_t>::min());

    ASSERT_EQ(parse_value_with_format<int32_t>("2147483648", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int32_t>("-2147483649", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int32_t>("-", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<int32_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__int64_t) {
    ASSERT_EQ(parse_value_with_format<int64_t>("9223372036854775807", "%d"), std::numeric_limits<int64_t>::max());
    ASSERT_EQ(parse_value_with_format<int64_t>("0", "%d"), 0);
    ASSERT_EQ(parse_value_with_format<int64_t>("-9223372036854775808", "%d"), std::numeric_limits<int64_t>::min());

    ASSERT_EQ(parse_value_with_format<int64_t>("9223372036854775808", "%d").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int64_t>("-9223372036854775809", "%d").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int64_t>("-", "%d").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<int64_t>("x", "%d").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__int64_t__without_specifier) {
    ASSERT_EQ(parse_value_with_format<int64_t>("9223372036854775807", ""), std::numeric_limits<int64_t>::max());
    ASSERT_EQ(parse_value_with_format<int64_t>("0", ""), 0);
    ASSERT_EQ(parse_value_with_format<int64_t>("-9223372036854775808", ""), std::numeric_limits<int64_t>::min());

    ASSERT_EQ(parse_value_with_format<int64_t>("9223372036854775808", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int64_t>("-9223372036854775809", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<int64_t>("-", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<int64_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__uint8_t) {
    ASSERT_EQ(parse_value_with_format<uint8_t>("255", "%u"), std::numeric_limits<uint8_t>::max());
    ASSERT_EQ(parse_value_with_format<uint8_t>("0", "%u"), std::numeric_limits<uint8_t>::min());

    ASSERT_EQ(parse_value_with_format<uint8_t>("256", "%u").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint8_t>("-1", "%u").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint8_t>("x", "%u").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__uint8_t__without_specifier) {
    ASSERT_EQ(parse_value_with_format<uint8_t>("255", ""), std::numeric_limits<uint8_t>::max());
    ASSERT_EQ(parse_value_with_format<uint8_t>("0", ""), std::numeric_limits<uint8_t>::min());

    ASSERT_EQ(parse_value_with_format<uint8_t>("256", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint8_t>("-1", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint8_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__uint16_t) {
    ASSERT_EQ(parse_value_with_format<uint16_t>("65535", "%u"), std::numeric_limits<uint16_t>::max());
    ASSERT_EQ(parse_value_with_format<uint16_t>("0", "%u"), std::numeric_limits<uint16_t>::min());

    ASSERT_EQ(parse_value_with_format<uint16_t>("65536", "%u").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint16_t>("-1", "%u").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint16_t>("x", "%u").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__uint16_t__without_specifier) {
    ASSERT_EQ(parse_value_with_format<uint16_t>("65535", ""), std::numeric_limits<uint16_t>::max());
    ASSERT_EQ(parse_value_with_format<uint16_t>("0", ""), std::numeric_limits<uint16_t>::min());

    ASSERT_EQ(parse_value_with_format<uint16_t>("65536", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint16_t>("-1", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint16_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__uint32_t) {
    ASSERT_EQ(parse_value_with_format<uint32_t>("4294967295", "%u"), std::numeric_limits<uint32_t>::max());
    ASSERT_EQ(parse_value_with_format<uint32_t>("0", "%u"), std::numeric_limits<uint32_t>::min());

    ASSERT_EQ(parse_value_with_format<uint32_t>("4294967296", "%u").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint32_t>("-1", "%u").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint32_t>("x", "%u").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__uint32_t__without_specifier) {
    ASSERT_EQ(parse_value_with_format<uint32_t>("4294967295", ""), std::numeric_limits<uint32_t>::max());
    ASSERT_EQ(parse_value_with_format<uint32_t>("0", ""), std::numeric_limits<uint32_t>::min());

    ASSERT_EQ(parse_value_with_format<uint32_t>("4294967296", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint32_t>("-1", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint32_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__uint64_t) {
    ASSERT_EQ(parse_value_with_format<uint64_t>("18446744073709551615", "%u"), std::numeric_limits<uint64_t>::max());
    ASSERT_EQ(parse_value_with_format<uint64_t>("0", "%u"), std::numeric_limits<uint64_t>::min());

    ASSERT_EQ(parse_value_with_format<uint64_t>("18446744073709551616", "%u").error().message,
              "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint64_t>("-1", "%u").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint64_t>("x", "%u").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__uint64_t__without_specifier) {
    ASSERT_EQ(parse_value_with_format<uint64_t>("18446744073709551615", ""), std::numeric_limits<uint64_t>::max());
    ASSERT_EQ(parse_value_with_format<uint64_t>("0", "%u"), std::numeric_limits<uint64_t>::min());

    ASSERT_EQ(parse_value_with_format<uint64_t>("18446744073709551616", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint64_t>("-1", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint64_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__float) {
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("3.402823e+38", "%f").value(), std::numeric_limits<float>::max());
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("0", "%f").value(), 0);
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("1.175494e-38", "%f").value(), std::numeric_limits<float>::min());

    ASSERT_EQ(parse_value_with_format<float>("3.402823e+39", "%f").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<float>("-3.402823e+39", "%f").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<float>("-", "%f").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<float>("x", "%f").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__float__without_specifier) {
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("3.402823e+38", "").value(), std::numeric_limits<float>::max());
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("0", "").value(), 0);
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("1.175494e-38", "").value(), std::numeric_limits<float>::min());

    ASSERT_EQ(parse_value_with_format<float>("3.402823e+39", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<float>("-3.402823e+39", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<float>("-", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<float>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__double) {
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("1.797693e+308", "%f").value(), std::numeric_limits<double>::max());
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("0", "%f").value(), 0);
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("2.225074e-308", "%f").value(), std::numeric_limits<double>::min());

    ASSERT_EQ(parse_value_with_format<double>("1.797693e+309", "%f").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<double>("-1.797693e+309", "%f").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<double>("-", "%f").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<double>("x", "%f").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__double__without_specifier) {
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("1.797693e+308", "").value(), std::numeric_limits<double>::max());
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("0", "").value(), 0);
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("2.225074e-308", "").value(), std::numeric_limits<double>::min());

    ASSERT_EQ(parse_value_with_format<double>("1.797693e+309", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<double>("-1.797693e+309", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<double>("-", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<double>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__empty_input_for_strings_returns_empty) {
    ASSERT_EQ(parse_value_with_format<std::string_view>("", "%s").value(), "");
    ASSERT_EQ(parse_value_with_format<std::string>("", "%s").value(), "");
    ASSERT_EQ(parse_value_with_format<std::string_view>(" ", "%s").value(), " ");
    ASSERT_EQ(parse_value_with_format<std::string>(" ", "%s").value(), " ");
}

TEST(ScanTest, parse_value_with_format__string_view) {
    ASSERT_EQ(parse_value_with_format<std::string_view>("Test", "%s"), "Test");
}

TEST(ScanTest, parse_value_with_format__string_view__without_specifier) {
    ASSERT_EQ(parse_value_with_format<std::string_view>("Test", ""), "Test");
}

TEST(ScanTest, parse_value_with_format__string) {
    ASSERT_EQ(parse_value_with_format<std::string>("Test", "%s"), "Test");
}

TEST(ScanTest, parse_value_with_format__string__without_specifier) {
    ASSERT_EQ(parse_value_with_format<std::string>("Test", ""), "Test");
}

TEST(ScanTest, SimpleTest) {
    auto result = stdx::scan<std::string>("number", "{}");
    ASSERT_FALSE(result);
}