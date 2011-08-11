/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#define TENUM_USE_SHORTCUTS 1
#include "tenum.hpp"

#define BOOST_TEST_MODULE tenum_static_enum_tests
#include <boost/test/unit_test.hpp>

lte_enum(static_enum,
    lte_ev(value1,2)
    lte_e(value2)
    lte_en(value3,"value_number_3"),
    ::boost::uint8_t
)

/**
 * @defgroup static_enum_tests Static enums test cases
 */BOOST_AUTO_TEST_SUITE(static_enum_tests)

/**
 * @class test_static_enum_from_enum_serialization
 * @brief Tests static enum serialization from enum constant.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_from_enum_serialization) {
  static_enum_t enum_value = static_cast< static_enum_t > (static_enum::value1);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"value1");
}

/**
 * @class test_static_enum_from_int_explicit_serialization
 * @brief Tests static enum serialization to explicit string equivalent from integer literal.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_from_int_explicit_serialization) {
  static_enum_t enum_value = static_cast< static_enum_t > (4);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"value_number_3");
}

/**
 * @class test_static_enum_deserialization
 * @brief Tests static enum deserialization.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_deserialization) {
  static_enum_t enum_value;
  ::std::string string_value = "value2";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (static_enum::value2));
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (3));
}

/**
 * @class test_static_enum_unknown_serialization
 * @brief Tests static enum unknown value serialization.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_unknown_serialization) {
  static_enum_t enum_value = static_cast< static_enum_t > (static_enum::lte_unknown);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"lte_unknown");
}

/**
 * @class test_static_enum_unknown_integer_serialization
 * @brief Tests static enum unknown value serialization from integer without enum equivalent.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_unknown_integer_serialization) {
  static_enum_t enum_value = static_cast< static_enum_t > (-1);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"lte_unknown");
}

/**
 * @class test_static_enum_empty_deserialization
 * @brief Tests static enum empty string deserialization to unknown value.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_empty_deserialization) {
  static_enum_t enum_value;
  ::std::string string_value = "";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (static_enum::lte_unknown));
}

/**
 * @class test_static_enum_unknown_deserialization
 * @brief Tests static enum unknown string deserialization to unknown value.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_unknown_deserialization) {
  static_enum_t enum_value;
  ::std::string string_value = "foobar";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (static_enum::lte_unknown));
}

/**
 * @class test_static_enum_integers_eq
 * @brief Tests static enum integer equality operator.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_integers_eq) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 4;
  BOOST_CHECK(integer_value == enum_value);
  BOOST_CHECK(enum_value == integer_value);
}

/**
 * @class test_static_enum_integers_neq
 * @brief Tests static enum integer inequality operator.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_integers_neq) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 0;
  BOOST_CHECK(integer_value != enum_value);
  BOOST_CHECK(enum_value != integer_value);
}

/**
 * @class test_static_enum_integers_bitwise_and
 * @brief Tests integer bitwise and operator with static enum.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_integers_bitwise_and) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value1 = 0b101 & enum_value;
  BOOST_CHECK(integer_value1 == 0b100);
  ::boost::uint64_t integer_value2 = enum_value & 0b101;
  BOOST_CHECK(integer_value2 == 0b100);
}

/**
 * @class test_static_enum_integers_bitwise_or
 * @brief Tests integer bitwise or operator with static enum.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_integers_bitwise_or) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value1 = 0b001 | enum_value;
  BOOST_CHECK(integer_value1 == 0b101);
  ::boost::uint64_t integer_value2 = enum_value | 0b001;
  BOOST_CHECK(integer_value2 == 0b101);
}

/**
 * @class test_static_enum_integers_bitwise_xor
 * @brief Tests integer bitwise xor operator with static enum.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_integers_bitwise_xor) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value1 = 0b101 ^ enum_value;
  BOOST_CHECK(integer_value1 == 0b001);
  ::boost::uint64_t integer_value2 = enum_value ^ 0b101;
  BOOST_CHECK(integer_value2 == 0b001);
}

/**
 * @class test_static_enum_integers_bitwise_and_assign
 * @brief Tests integer bitwise and assignation operator with static enum.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_integers_bitwise_and_assign) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 0b101;
  integer_value &= enum_value;
  BOOST_CHECK(integer_value == 0b100);
}

/**
 * @class test_static_enum_integers_bitwise_or_assign
 * @brief Tests integer bitwise or assignation operator with static enum.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_integers_bitwise_or_assign) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 0b001;
  integer_value |= enum_value;
  BOOST_CHECK(integer_value == 0b101);
}

/**
 * @class test_static_enum_integers_bitwise_xor_assign
 * @brief Tests integer bitwise xor assignation operator with static enum.
 * @ingroup static_enum_tests
 */
BOOST_AUTO_TEST_CASE(test_static_enum_integers_bitwise_xor_assign) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 0b101;
  integer_value ^= enum_value;
  BOOST_CHECK(integer_value == 0b001);
}

BOOST_AUTO_TEST_SUITE_END()
