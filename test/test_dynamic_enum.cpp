/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#define TENUM_USE_SHORTCUTS 1
#include "tenum.hpp"

#define BOOST_TEST_MODULE tenum_dynamic_enum_tests
#include <boost/test/unit_test.hpp>

lte_dynamic_enum(dynamic_enum,
    lte_ev(value1,2)
    lte_evn(value2,5,"test_value2")
    lte_e(value3),
    value3+10,
    ::boost::uint16_t
)

/**
 * @defgroup dynamic_enum_tests Dynamic enums test cases
 */BOOST_AUTO_TEST_SUITE(dynamic_enum_tests)

/**
 * @class test_dynamic_enum_from_offset_serialization
 * @brief Tests dynamic enum construction from computed constant and serialization.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_from_offset_serialization) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (dynamic_enum::value2 - 1);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  // (value2 - 1) is 4, which is (value1 + 2)
  BOOST_CHECK_EQUAL(string_value,"value1#2");
}

/**
 * @class test_dynamic_enum_serialization_explicit
 * @brief Tests dynamic enum serialization with an explicit string equivalent.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_serialization_explicit) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (dynamic_enum::value2);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"test_value2");
}

/**
 * @class test_dynamic_enum_from_integer_serialization
 * @brief Tests dynamic enum serialization from an integer value.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_from_integer_serialization) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (3);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"value1#1");
}

/**
 * @class test_dynamic_enum_deserialization
 * @brief Tests dynamic enum deserialization with offset and comparison to integer and enum values.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_deserialization) {
  dynamic_enum_t enum_value;
  ::std::string string_value = "value3#4";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (dynamic_enum::value3 + 4));
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (10));
}

/**
 * @class test_dynamic_enum_unknown_serialization
 * @brief Tests dynamic enum unknown value serialization.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_unknown_serialization) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"lte_unknown");
}

/**
 * @class test_dynamic_enum_out_of_range_serialization
 * @brief Tests dynamic enum out of range value serialization to unknown.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_out_of_range_serialization) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (0);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"lte_unknown");
}

/**
 * @class test_dynamic_enum_out_of_range_deserialization
 * @brief Tests dynamic enum out of range value deserialization to unknown.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_out_of_range_deserialization) {
  dynamic_enum_t enum_value;
  ::std::string string_value = "value3#123456789";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown));
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (static_cast< int >(dynamic_enum::value3+10)));
}

/**
 * @class test_dynamic_enum_empty_deserialization
 * @brief Tests dynamic enum empty string deserialization to unknown constant.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_empty_deserialization) {
  dynamic_enum_t enum_value;
  ::std::string string_value = "";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown));
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (static_cast< int >(dynamic_enum::value3+10)));
}

/**
 * @class test_dynamic_enum_correct_deserialization
 * @brief Tests dynamic enum value deserialization and serialization to correct value.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_correct_deserialization) {
  dynamic_enum_t enum_value;
  ::std::string string_value = "value1#3";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;

  ::std::stringstream outstream;
  outstream << enum_value;
  outstream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"test_value2");
}

/**
 * @class test_dynamic_enum_integers_eq
 * @brief Tests dynamic enum integer equality operator.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_eq) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 2;
  BOOST_CHECK(integer_value == enum_value);
  BOOST_CHECK(enum_value == integer_value);
}

/**
 * @class test_dynamic_enum_integers_neq
 * @brief Tests dynamic enum integer inequality operator.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_neq) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 0;
  BOOST_CHECK(integer_value != enum_value);
  BOOST_CHECK(enum_value != integer_value);
}

/**
 * @class test_dynamic_enum_integers_bitwise_and
 * @brief Tests integer bitwise and operator with dynamic enum.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_bitwise_and) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value1 = 0b011 & enum_value;
  BOOST_CHECK(integer_value1 == 0b010);
  ::boost::uint64_t integer_value2 = enum_value & 0b011;
  BOOST_CHECK(integer_value2 == 0b010);
}

/**
 * @class test_dynamic_enum_integers_bitwise_or
 * @brief Tests integer bitwise or operator with dynamic enum.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_bitwise_or) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value1 = 0b001 | enum_value;
  BOOST_CHECK(integer_value1 == 0b011);
  ::boost::uint64_t integer_value2 = enum_value | 0b001;
  BOOST_CHECK(integer_value2 == 0b011);
}

/**
 * @class test_dynamic_enum_integers_bitwise_xor
 * @brief Tests integer bitwise xor operator with dynamic enum.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_bitwise_xor) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value1 = 0b011 ^ enum_value;
  BOOST_CHECK(integer_value1 == 0b001);
  ::boost::uint64_t integer_value2 = enum_value ^ 0b011;
  BOOST_CHECK(integer_value2 == 0b001);
}

/**
 * @class test_dynamic_enum_integers_bitwise_and_assign
 * @brief Tests integer bitwise and assignation operator with dynamic enum.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_bitwise_and_assign) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 0b011;
  integer_value &= enum_value;
  BOOST_CHECK(integer_value == 0b010);
}

/**
 * @class test_dynamic_enum_integers_bitwise_or_assign
 * @brief Tests integer bitwise or assignation operator with dynamic enum.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_bitwise_or_assign) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 0b001;
  integer_value |= enum_value;
  BOOST_CHECK(integer_value == 0b011);
}

/**
 * @class test_dynamic_enum_integers_bitwise_xor_assign
 * @brief Tests integer bitwise xor assignation operator with dynamic enum.
 * @ingroup dynamic_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_bitwise_xor_assign) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 0b011;
  integer_value ^= enum_value;
  BOOST_CHECK(integer_value == 0b001);
}

BOOST_AUTO_TEST_SUITE_END()
