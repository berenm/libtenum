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
    lte_e(value3)
)

BOOST_AUTO_TEST_SUITE(static_enum_tests)

BOOST_AUTO_TEST_CASE(test_static_enum_1) {
  static_enum_t enum_value = static_cast< static_enum_t > (static_enum::value1);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"value1");
}

BOOST_AUTO_TEST_CASE(test_static_enum_2) {
  static_enum_t enum_value = static_cast< static_enum_t > (4);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"value3");
}

BOOST_AUTO_TEST_CASE(test_static_enum_3) {
  static_enum_t enum_value;
  ::std::string string_value = "value2";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (static_enum::value2));
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (3));
}

BOOST_AUTO_TEST_CASE(test_static_enum_4) {
  static_enum_t enum_value = static_cast< static_enum_t > (static_enum::lte_unknown);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"lte_unknown");
}

BOOST_AUTO_TEST_CASE(test_static_enum_5) {
  static_enum_t enum_value = static_cast< static_enum_t > (-1);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"lte_unknown");
}

BOOST_AUTO_TEST_CASE(test_static_enum_6) {
  static_enum_t enum_value;
  ::std::string string_value = "";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (static_enum::lte_unknown));
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (-1));
}

BOOST_AUTO_TEST_CASE(test_static_enum_integers_1) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 4;
  BOOST_CHECK(integer_value == enum_value);
  BOOST_CHECK(enum_value == integer_value);
}

BOOST_AUTO_TEST_CASE(test_static_enum_integers_2) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 0;
  BOOST_CHECK(integer_value != enum_value);
  BOOST_CHECK(enum_value != integer_value);
}

BOOST_AUTO_TEST_CASE(test_static_enum_integers_3) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value1 = 0b101 & enum_value;
  BOOST_CHECK(integer_value1 == 0b100);
  ::boost::uint64_t integer_value2 = enum_value & 0b101;
  BOOST_CHECK(integer_value2 == 0b100);
}

BOOST_AUTO_TEST_CASE(test_static_enum_integers_4) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value1 = 0b001 | enum_value;
  BOOST_CHECK(integer_value1 == 0b101);
  ::boost::uint64_t integer_value2 = enum_value | 0b001;
  BOOST_CHECK(integer_value2 == 0b101);
}

BOOST_AUTO_TEST_CASE(test_static_enum_integers_5) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value1 = 0b101 ^ enum_value;
  BOOST_CHECK(integer_value1 == 0b001);
  ::boost::uint64_t integer_value2 = enum_value ^ 0b101;
  BOOST_CHECK(integer_value2 == 0b001);
}

BOOST_AUTO_TEST_CASE(test_static_enum_integers_6) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 0b101;
  integer_value &= enum_value;
  BOOST_CHECK(integer_value == 0b100);
}

BOOST_AUTO_TEST_CASE(test_static_enum_integers_7) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 0b001;
  integer_value |= enum_value;
  BOOST_CHECK(integer_value == 0b101);
}

BOOST_AUTO_TEST_CASE(test_static_enum_integers_8) {
  static_enum_t enum_value = static_enum::value3;
  ::boost::uint64_t integer_value = 0b101;
  integer_value ^= enum_value;
  BOOST_CHECK(integer_value == 0b001);
}

BOOST_AUTO_TEST_SUITE_END()
