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
    ASSERT_FALSE(is_supported_type_v<char *>);

    ASSERT_FALSE(is_supported_type_v<const char>);
    ASSERT_FALSE(is_supported_type_v<const void *>);
    ASSERT_FALSE(is_supported_type_v<const char *>);
}

TEST(ScanTest, parse_value_with_format__invalid_specifier__returns_error) {
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "x").error().message, "Incorrect specifier size");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "%x").error().message, "Expected specifier %d");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", " d").error().message, "Expected specifier %d");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "d").error().message, "Incorrect specifier size");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "u").error().message, "Incorrect specifier size");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "f").error().message, "Incorrect specifier size");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "s").error().message, "Incorrect specifier size");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "%u").error().message, "Expected specifier %d");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "%s").error().message, "Expected specifier %d");
    ASSERT_EQ(parse_value_with_format<int8_t>("0", "%f").error().message, "Expected specifier %d");
    ASSERT_EQ(parse_value_with_format<uint8_t>("0", "%d").error().message, "Expected specifier %u");
    ASSERT_EQ(parse_value_with_format<uint8_t>("0", "%s").error().message, "Expected specifier %u");
    ASSERT_EQ(parse_value_with_format<uint8_t>("0", "%f").error().message, "Expected specifier %u");
    ASSERT_EQ(parse_value_with_format<float>("0", "%d").error().message, "Expected specifier %f");
    ASSERT_EQ(parse_value_with_format<float>("0", "%u").error().message, "Expected specifier %f");
    ASSERT_EQ(parse_value_with_format<float>("0", "%s").error().message, "Expected specifier %f");
    ASSERT_EQ(parse_value_with_format<double>("0", "%d").error().message, "Expected specifier %f");
    ASSERT_EQ(parse_value_with_format<double>("0", "%u").error().message, "Expected specifier %f");
    ASSERT_EQ(parse_value_with_format<double>("0", "%s").error().message, "Expected specifier %f");
    ASSERT_EQ(parse_value_with_format<std::string_view>("a", "%d").error().message, "Expected specifier %s");
    ASSERT_EQ(parse_value_with_format<std::string_view>("a", "%u").error().message, "Expected specifier %s");
    ASSERT_EQ(parse_value_with_format<std::string_view>("a", "%f").error().message, "Expected specifier %s");
    ASSERT_EQ(parse_value_with_format<std::string>("a", "%d").error().message, "Expected specifier %s");
    ASSERT_EQ(parse_value_with_format<std::string>("a", "%u").error().message, "Expected specifier %s");
    ASSERT_EQ(parse_value_with_format<std::string>("a", "%f").error().message, "Expected specifier %s");
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
    ASSERT_EQ(parse_value_with_format<int64_t>("-9223372036854775809", "%d").error().message,
              "Conversion out of range");
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
    ASSERT_EQ(parse_value_with_format<uint64_t>("0", ""), std::numeric_limits<uint64_t>::min());

    ASSERT_EQ(parse_value_with_format<uint64_t>("18446744073709551616", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<uint64_t>("-1", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<uint64_t>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__float) {
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("3.402823e+38", "%f").value(), std::numeric_limits<float>::max());
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("0.0", "%f").value(), 0);
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("1.175494e-38", "%f").value(), std::numeric_limits<float>::min());

    ASSERT_EQ(parse_value_with_format<float>("3.402823e+39", "%f").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<float>("-3.402823e+39", "%f").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<float>("-", "%f").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<float>("x", "%f").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__float__without_specifier) {
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("3.402823e+38", "").value(), std::numeric_limits<float>::max());
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("0.0", "").value(), 0);
    ASSERT_FLOAT_EQ(parse_value_with_format<float>("1.175494e-38", "").value(), std::numeric_limits<float>::min());

    ASSERT_EQ(parse_value_with_format<float>("3.402823e+39", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<float>("-3.402823e+39", "").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<float>("-", "").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<float>("x", "").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__double) {
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("1.797693e+308", "%f").value(), std::numeric_limits<double>::max());
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("0.0", "%f").value(), 0);
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("2.225074e-308", "%f").value(), std::numeric_limits<double>::min());

    ASSERT_EQ(parse_value_with_format<double>("1.797693e+309", "%f").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<double>("-1.797693e+309", "%f").error().message, "Conversion out of range");
    ASSERT_EQ(parse_value_with_format<double>("-", "%f").error().message, "Conversion failed");
    ASSERT_EQ(parse_value_with_format<double>("x", "%f").error().message, "Conversion failed");
}

TEST(ScanTest, parse_value_with_format__double__without_specifier) {
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("1.797693e+308", "").value(), std::numeric_limits<double>::max());
    ASSERT_FLOAT_EQ(parse_value_with_format<double>("0.0", "").value(), 0);
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

TEST(ScanTest, scan_2_vars_with_specifiers) {
    auto result =
        stdx::scan<int32_t, float>("I want to sum 42 and 3.14 numbers.", "I want to sum {%d} and {%f} numbers.");
    ASSERT_TRUE(result.has_value());
    auto values = result.value().values;
    ASSERT_EQ(std::get<0>(values), 42);
    ASSERT_FLOAT_EQ(std::get<1>(values), 3.14f);
}

TEST(ScanTest, scan_2_vars_without_specifiers) {
    auto result = stdx::scan<int32_t, float>("I want to sum 42 and 3.14 numbers.", "I want to sum {} and {} numbers.");
    ASSERT_TRUE(result.has_value());
    auto values = result.value().values;
    ASSERT_EQ(std::get<0>(values), 42);
    ASSERT_FLOAT_EQ(std::get<1>(values), 3.14f);
}

TEST(ScanTest, scan_2_vars_with_and_without_specifiers) {
    auto result =
        stdx::scan<int32_t, float>("I want to sum 42 and 3.14 numbers.", "I want to sum {%d} and {} numbers.");
    ASSERT_TRUE(result.has_value());
    auto values = result.value().values;
    ASSERT_EQ(std::get<0>(values), 42);
    ASSERT_FLOAT_EQ(std::get<1>(values), 3.14f);
}

TEST(ScanTest, scan_returns_all_supported_types_without_specifiers) {
    auto result =
        stdx::scan<int8_t, int8_t, int16_t, int16_t, int32_t, int32_t, int64_t, int64_t, uint8_t, uint8_t, uint16_t,
                   uint16_t, uint32_t, uint32_t, uint64_t, uint64_t, float, float, double, double, std::string_view,
                   std::string>("int8_t:127 -128, int16_t:32767 -32768, int32_t:2147483647 -2147483648, "
                                "int64_t:9223372036854775807 -9223372036854775808, uint8_t:255 0, "
                                "uint16_t:65535 0, uint32_t:4294967295 0, "
                                "uint64_t:18446744073709551615 0, float:3.402823e+38 1.175494e-38, "
                                "double:1.797693e+308 2.225074e-308, string_view:abcdef, string:ghij",

                                "int8_t:{} {}, int16_t:{} {}, int32_t:{} {}, "
                                "int64_t:{} {}, uint8_t:{} {}, "
                                "uint16_t:{} {}, uint32_t:{} {}, "
                                "uint64_t:{} {}, float:{} {}, "
                                "double:{} {}, string_view:{}, string:{}");
    ASSERT_TRUE(result.has_value());
    auto values = result.value().values;
    ASSERT_EQ(std::tuple_size_v<decltype(values)>, 22);
    ASSERT_EQ(std::get<0>(values), std::numeric_limits<int8_t>::max());
    ASSERT_EQ(std::get<1>(values), std::numeric_limits<int8_t>::min());
    ASSERT_EQ(std::get<2>(values), std::numeric_limits<int16_t>::max());
    ASSERT_EQ(std::get<3>(values), std::numeric_limits<int16_t>::min());
    ASSERT_EQ(std::get<4>(values), std::numeric_limits<int32_t>::max());
    ASSERT_EQ(std::get<5>(values), std::numeric_limits<int32_t>::min());
    ASSERT_EQ(std::get<6>(values), std::numeric_limits<int64_t>::max());
    ASSERT_EQ(std::get<7>(values), std::numeric_limits<int64_t>::min());
    ASSERT_EQ(std::get<8>(values), std::numeric_limits<uint8_t>::max());
    ASSERT_EQ(std::get<9>(values), std::numeric_limits<uint8_t>::min());
    ASSERT_EQ(std::get<10>(values), std::numeric_limits<uint16_t>::max());
    ASSERT_EQ(std::get<11>(values), std::numeric_limits<uint16_t>::min());
    ASSERT_EQ(std::get<12>(values), std::numeric_limits<uint32_t>::max());
    ASSERT_EQ(std::get<13>(values), std::numeric_limits<uint32_t>::min());
    ASSERT_EQ(std::get<14>(values), std::numeric_limits<uint64_t>::max());
    ASSERT_EQ(std::get<15>(values), std::numeric_limits<uint64_t>::min());
    ASSERT_FLOAT_EQ(std::get<16>(values), std::numeric_limits<float>::max());
    ASSERT_FLOAT_EQ(std::get<17>(values), std::numeric_limits<float>::min());
    ASSERT_FLOAT_EQ(std::get<18>(values), std::numeric_limits<double>::max());
    ASSERT_FLOAT_EQ(std::get<19>(values), std::numeric_limits<double>::min());
    ASSERT_EQ(std::get<20>(values), "abcdef");
    ASSERT_EQ(std::get<21>(values), "ghij");
}

TEST(ScanTest, scan_returns_all_supported_types_with_specifiers) {
    auto result =
        stdx::scan<int8_t, int8_t, int16_t, int16_t, int32_t, int32_t, int64_t, int64_t, uint8_t, uint8_t, uint16_t,
                   uint16_t, uint32_t, uint32_t, uint64_t, uint64_t, float, float, double, double, std::string_view,
                   std::string>("int8_t:127 -128, int16_t:32767 -32768, int32_t:2147483647 -2147483648, "
                                "int64_t:9223372036854775807 -9223372036854775808, uint8_t:255 0, "
                                "uint16_t:65535 0, uint32_t:4294967295 0, "
                                "uint64_t:18446744073709551615 0, float:3.402823e+38 1.175494e-38, "
                                "double:1.797693e+308 2.225074e-308, string_view:abcdef, string:ghij",

                                "int8_t:{%d} {%d}, int16_t:{%d} {%d}, int32_t:{%d} {%d}, "
                                "int64_t:{%d} {%d}, uint8_t:{%u} {%u}, "
                                "uint16_t:{%u} {%u}, uint32_t:{%u} {%u}, "
                                "uint64_t:{%u} {%u}, float:{%f} {%f}, "
                                "double:{%f} {%f}, string_view:{%s}, string:{%s}");
    ASSERT_TRUE(result.has_value());
    auto values = result.value().values;
    ASSERT_EQ(std::tuple_size_v<decltype(values)>, 22);
    ASSERT_EQ(std::get<0>(values), std::numeric_limits<int8_t>::max());
    ASSERT_EQ(std::get<1>(values), std::numeric_limits<int8_t>::min());
    ASSERT_EQ(std::get<2>(values), std::numeric_limits<int16_t>::max());
    ASSERT_EQ(std::get<3>(values), std::numeric_limits<int16_t>::min());
    ASSERT_EQ(std::get<4>(values), std::numeric_limits<int32_t>::max());
    ASSERT_EQ(std::get<5>(values), std::numeric_limits<int32_t>::min());
    ASSERT_EQ(std::get<6>(values), std::numeric_limits<int64_t>::max());
    ASSERT_EQ(std::get<7>(values), std::numeric_limits<int64_t>::min());
    ASSERT_EQ(std::get<8>(values), std::numeric_limits<uint8_t>::max());
    ASSERT_EQ(std::get<9>(values), std::numeric_limits<uint8_t>::min());
    ASSERT_EQ(std::get<10>(values), std::numeric_limits<uint16_t>::max());
    ASSERT_EQ(std::get<11>(values), std::numeric_limits<uint16_t>::min());
    ASSERT_EQ(std::get<12>(values), std::numeric_limits<uint32_t>::max());
    ASSERT_EQ(std::get<13>(values), std::numeric_limits<uint32_t>::min());
    ASSERT_EQ(std::get<14>(values), std::numeric_limits<uint64_t>::max());
    ASSERT_EQ(std::get<15>(values), std::numeric_limits<uint64_t>::min());
    ASSERT_FLOAT_EQ(std::get<16>(values), std::numeric_limits<float>::max());
    ASSERT_FLOAT_EQ(std::get<17>(values), std::numeric_limits<float>::min());
    ASSERT_FLOAT_EQ(std::get<18>(values), std::numeric_limits<double>::max());
    ASSERT_FLOAT_EQ(std::get<19>(values), std::numeric_limits<double>::min());
    ASSERT_EQ(std::get<20>(values), "abcdef");
    ASSERT_EQ(std::get<21>(values), "ghij");
}

TEST(ScanTest, scan_returns_error_if_argument_count_mismatch) {
    auto result0 = stdx::scan<int8_t>("int8_t:127 -128", "int8_t:{%d} {%d}");
    ASSERT_EQ(result0.error().message, "Argument count mismatch");

    auto result1 = stdx::scan<int8_t, int8_t>("int8_t:127", "int8_t:{%d}");
    ASSERT_EQ(result1.error().message, "Argument count mismatch");
}

TEST(ScanTest, scan_returns_error_if_incorrect_specifier) {
    auto result = stdx::scan<int8_t>("1", "{x}");
    ASSERT_EQ(result.error().message, "Incorrect specifier size");
}

TEST(ScanTest, scan_returns_error_if_input_empty) {
    auto result = stdx::scan<int8_t>("", "{%d}");
    ASSERT_EQ(result.error().message, "Empty input");
}

TEST(ScanTest, scan_returns_error_if_wrong_conversion) {
    auto result = stdx::scan<int8_t>("abcd", "{%d}");
    ASSERT_EQ(result.error().message, "Conversion failed");
}

TEST(ScanTest, scan_returns_error_if_conversion_is_out_of_range) {
    auto result = stdx::scan<int8_t>("128", "{%d}");
    ASSERT_EQ(result.error().message, "Conversion out of range");
}

TEST(ScanTest, scan_returns_error_if_placeholders_do_not_match) {
    auto result = stdx::scan<int8_t>("0", "{%d");
    ASSERT_EQ(result.error().message, "Unformatted text in input and format string are different");
}

TEST(ScanTest, scan_returns_error_if_input_do_not_match_format) {
    auto result0 = stdx::scan<int8_t>("abcd 0", "abc {%d}");
    ASSERT_EQ(result0.error().message, "Unformatted text in input and format string are different");

    auto result1 = stdx::scan<int8_t>("abc 0", "abcd {%d}");
    ASSERT_EQ(result1.error().message, "Unformatted text in input and format string are different");
}

TEST(ScanTest, scan_returns_error_if_types_do_not_match) {
    auto result = stdx::scan<int8_t>("int8_t:127", "int8_t:{%f}");
    ASSERT_EQ(result.error().message, "Expected specifier %d");
}
