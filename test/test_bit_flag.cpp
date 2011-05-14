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

lte_bit_flag(bit_flag,
    lte_ev(bit1,0b001)
    lte_ev(bit2,0b010)
    lte_ev(bit3,0b100)
)

BOOST_AUTO_TEST_SUITE(bit_flag_tests)

BOOST_AUTO_TEST_CASE(test_bit_flag_1) {
  bit_flag_t enum_value = static_cast< bit_flag_t > (bit_flag::bit1 | bit_flag::bit2);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit1+bit2");
}

BOOST_AUTO_TEST_CASE(test_bit_flag_2) {
  bit_flag_t enum_value = static_cast< bit_flag_t > (0b110);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit2+bit3");
}

BOOST_AUTO_TEST_CASE(test_bit_flag_3) {
  bit_flag_t enum_value;
  ::std::string string_value = "bit1+bit3";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< bit_flag_t > (bit_flag::bit1 | bit_flag::bit3));
  BOOST_CHECK_EQUAL(enum_value,static_cast< bit_flag_t > (0b101));
}

BOOST_AUTO_TEST_CASE(test_bit_flag_4) {
  bit_flag_t enum_value = static_cast< bit_flag_t > (bit_flag::bit1 | bit_flag::bit2);
  enum_value = static_cast< bit_flag_t > (enum_value | bit_flag::bit3);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit1+bit2+bit3");
}

BOOST_AUTO_TEST_CASE(test_bit_flag_5) {
  bit_flag_t enum_value = static_cast< bit_flag_t > (bit_flag::bit1 | bit_flag::bit2);
  enum_value = static_cast< bit_flag_t > (enum_value ^ bit_flag::bit2);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit1");
}

BOOST_AUTO_TEST_CASE(test_bit_flag_6) {
  bit_flag_t enum_value = static_cast< bit_flag_t > (0);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"");
}

BOOST_AUTO_TEST_CASE(test_bit_flag_7) {
  bit_flag_t enum_value;
  ::std::string string_value = "";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< bit_flag_t > (0));
}

BOOST_AUTO_TEST_SUITE_END()
