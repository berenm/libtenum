/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#define BOOST_TEST_MODULE TENUM_test
#include <boost/test/unit_test.hpp>

#define TENUM_USE_SHORTCUTS 1
#include "tenum.hpp"

lte_enum_s(static_enum,
    (value1)(value2)(value3)
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
  static_enum_t enum_value = static_cast< static_enum_t > (2);
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
  BOOST_CHECK_EQUAL(enum_value,static_cast< static_enum_t > (1));
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

BOOST_AUTO_TEST_SUITE_END()
