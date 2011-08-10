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

BOOST_AUTO_TEST_SUITE(dynamic_enum_tests)

BOOST_AUTO_TEST_CASE(test_dynamic_enum_1) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (dynamic_enum::value2 - 1);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  // (value2 - 1) is 4, which is (value1 + 2)
  BOOST_CHECK_EQUAL(string_value,"value1#2");
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_2) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (dynamic_enum::value2);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"test_value2");
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_3) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (3);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"value1#1");
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_4) {
  dynamic_enum_t enum_value;
  ::std::string string_value = "value3#4";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (dynamic_enum::value3 + 4));
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (10));
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_5) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"lte_unknown");
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_6) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (0);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"lte_unknown");
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_7) {
  dynamic_enum_t enum_value;
  ::std::string string_value = "";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown));
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (static_cast< int >(dynamic_enum::value3+10)));
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_8) {
  dynamic_enum_t enum_value = static_cast< dynamic_enum_t > (dynamic_enum::value3+9);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"value3#9");
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_9) {
  dynamic_enum_t enum_value;
  ::std::string string_value = "value3#9";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown - 1));
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (static_cast< int >(dynamic_enum::value3+9)));
}
BOOST_AUTO_TEST_CASE(test_dynamic_enum_10) {
  dynamic_enum_t enum_value;
  ::std::string string_value = "value3#123456789";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown));
  BOOST_CHECK_EQUAL(enum_value,static_cast< dynamic_enum_t > (static_cast< int >(dynamic_enum::value3+10)));
}
BOOST_AUTO_TEST_CASE(test_dynamic_enum_11) {
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

BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_1) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 2;
  BOOST_CHECK(integer_value == enum_value);
  BOOST_CHECK(enum_value == integer_value);
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_2) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 0;
  BOOST_CHECK(integer_value != enum_value);
  BOOST_CHECK(enum_value != integer_value);
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_3) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value1 = 0b011 & enum_value;
  BOOST_CHECK(integer_value1 == 0b010);
  ::boost::uint64_t integer_value2 = enum_value & 0b011;
  BOOST_CHECK(integer_value2 == 0b010);
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_4) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value1 = 0b001 | enum_value;
  BOOST_CHECK(integer_value1 == 0b011);
  ::boost::uint64_t integer_value2 = enum_value | 0b001;
  BOOST_CHECK(integer_value2 == 0b011);
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_5) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value1 = 0b011 ^ enum_value;
  BOOST_CHECK(integer_value1 == 0b001);
  ::boost::uint64_t integer_value2 = enum_value ^ 0b011;
  BOOST_CHECK(integer_value2 == 0b001);
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_6) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 0b011;
  integer_value &= enum_value;
  BOOST_CHECK(integer_value == 0b010);
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_7) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 0b001;
  integer_value |= enum_value;
  BOOST_CHECK(integer_value == 0b011);
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum_integers_8) {
  dynamic_enum_t enum_value = dynamic_enum::value1;
  ::boost::uint64_t integer_value = 0b011;
  integer_value ^= enum_value;
  BOOST_CHECK(integer_value == 0b001);
}

BOOST_AUTO_TEST_SUITE_END()
