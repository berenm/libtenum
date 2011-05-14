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

lte_dynamic_enum(dynamic_enum,
    lte_ev(value1,2)
    lte_evn(value2,5,"test_value2")
    lte_e(value3)
)

lte_bit_flag(bit_flag,
    lte_ev(bit1,0b001)
    lte_ev(bit2,0b010)
    lte_ev(bit3,0b100)
)

BOOST_AUTO_TEST_SUITE(basic_enum_tests)

BOOST_AUTO_TEST_CASE(test_static_enum) {
  static_enum_t enum_value1 = static_cast< static_enum_t > (static_enum::value1);
  ::std::string string_value1;
  ::std::stringstream stream1;
  stream1 << enum_value1;
  stream1 >> string_value1;
  BOOST_CHECK_EQUAL(string_value1,"value1");

  static_enum_t enum_value2 = static_cast< static_enum_t > (2);
  ::std::string string_value2;
  ::std::stringstream stream2;
  stream2 << enum_value2;
  stream2 >> string_value2;
  BOOST_CHECK_EQUAL(string_value2,"value3");

  static_enum_t enum_value3;
  ::std::string string_value3 = "value2";
  ::std::stringstream stream3;
  stream3 << string_value3;
  stream3 >> enum_value3;
  BOOST_CHECK_EQUAL(enum_value3,static_cast< static_enum_t > (static_enum::value2));
  BOOST_CHECK_EQUAL(enum_value3,static_cast< static_enum_t > (1));

  static_enum_t enum_value5 = static_cast< static_enum_t > (static_enum::lte_unknown);
  ::std::string string_value5;
  ::std::stringstream stream5;
  stream5 << enum_value5;
  stream5 >> string_value5;
  BOOST_CHECK_EQUAL(string_value5,"lte_unknown");

  static_enum_t enum_value6 = static_cast< static_enum_t > (-1);
  ::std::string string_value6;
  ::std::stringstream stream6;
  stream6 << enum_value6;
  stream6 >> string_value6;
  BOOST_CHECK_EQUAL(string_value6,"lte_unknown");

  static_enum_t enum_value7;
  ::std::string string_value7 = "";
  ::std::stringstream stream7;
  stream7 << string_value7;
  stream7 >> enum_value7;
  BOOST_CHECK_EQUAL(enum_value7,static_cast< static_enum_t > (static_enum::lte_unknown));
  BOOST_CHECK_EQUAL(enum_value7,static_cast< static_enum_t > (-1));
}

BOOST_AUTO_TEST_CASE(test_dynamic_enum) {
  dynamic_enum_t enum_value1 = static_cast< dynamic_enum_t > (dynamic_enum::value2 - 1);
  ::std::string string_value1;
  ::std::stringstream stream1;
  stream1 << enum_value1;
  stream1 >> string_value1;
  // (value2 - 1) is 4, which is (value1 + 2)
  BOOST_CHECK_EQUAL(string_value1,"value1#2");

  dynamic_enum_t enum_value2 = static_cast< dynamic_enum_t > (dynamic_enum::value2);
  ::std::string string_value2;
  ::std::stringstream stream2;
  stream2 << enum_value2;
  stream2 >> string_value2;
  BOOST_CHECK_EQUAL(string_value2,"test_value2");

  dynamic_enum_t enum_value3 = static_cast< dynamic_enum_t > (3);
  ::std::string string_value3;
  ::std::stringstream stream3;
  stream3 << enum_value3;
  stream3 >> string_value3;
  BOOST_CHECK_EQUAL(string_value3,"value1#1");

  dynamic_enum_t enum_value4;
  ::std::string string_value4 = "value3#4";
  ::std::stringstream stream4;
  stream4 << string_value4;
  stream4 >> enum_value4;
  BOOST_CHECK_EQUAL(enum_value4,static_cast< dynamic_enum_t > (dynamic_enum::value3 + 4));
  BOOST_CHECK_EQUAL(enum_value4,static_cast< dynamic_enum_t > (10));

  dynamic_enum_t enum_value5 = static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown);
  ::std::string string_value5;
  ::std::stringstream stream5;
  stream5 << enum_value5;
  stream5 >> string_value5;
  BOOST_CHECK_EQUAL(string_value5,"lte_unknown");

  dynamic_enum_t enum_value6 = static_cast< dynamic_enum_t > (-1);
  ::std::string string_value6;
  ::std::stringstream stream6;
  stream6 << enum_value6;
  stream6 >> string_value6;
  BOOST_CHECK_EQUAL(string_value6,"lte_unknown");

  dynamic_enum_t enum_value7;
  ::std::string string_value7 = "";
  ::std::stringstream stream7;
  stream7 << string_value7;
  stream7 >> enum_value7;
  BOOST_CHECK_EQUAL(enum_value7,static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown));
  BOOST_CHECK_EQUAL(enum_value7,static_cast< dynamic_enum_t > (-1));

  dynamic_enum_t enum_value8 = static_cast< dynamic_enum_t > (-2);
  ::std::string string_value8;
  ::std::stringstream stream8;
  stream8 << enum_value8;
  stream8 >> string_value8;
  BOOST_CHECK_EQUAL(string_value8,"value3#18446744073709551608");

  dynamic_enum_t enum_value9;
  ::std::string string_value9 = "value3#18446744073709551608";
  ::std::stringstream stream9;
  stream9 << string_value9;
  stream9 >> enum_value9;
  BOOST_CHECK_EQUAL(enum_value9,static_cast< dynamic_enum_t > (dynamic_enum::lte_unknown - 1));
  BOOST_CHECK_EQUAL(enum_value9,static_cast< dynamic_enum_t > (-2));
}

BOOST_AUTO_TEST_CASE(test_bit_flag) {
  bit_flag_t enum_value1 = static_cast< bit_flag_t > (bit_flag::bit1 | bit_flag::bit2);
  ::std::string string_value1;
  ::std::stringstream stream1;
  stream1 << enum_value1;
  stream1 >> string_value1;
  BOOST_CHECK_EQUAL(string_value1,"bit1+bit2");

  bit_flag_t enum_value2 = static_cast< bit_flag_t > (0b110);
  ::std::string string_value2;
  ::std::stringstream stream2;
  stream2 << enum_value2;
  stream2 >> string_value2;
  BOOST_CHECK_EQUAL(string_value2,"bit2+bit3");

  bit_flag_t enum_value3;
  ::std::string string_value3 = "bit1+bit3";
  ::std::stringstream stream3;
  stream3 << string_value3;
  stream3 >> enum_value3;
  BOOST_CHECK_EQUAL(enum_value3,static_cast< bit_flag_t > (bit_flag::bit1 | bit_flag::bit3));
  BOOST_CHECK_EQUAL(enum_value3,static_cast< bit_flag_t > (0b101));

  bit_flag_t enum_value4 = static_cast< bit_flag_t > (bit_flag::bit1 | bit_flag::bit2);
  enum_value4 |= bit_flag::bit3;
  ::std::string string_value4;
  ::std::stringstream stream4;
  stream4 << enum_value4;
  stream4 >> string_value4;
  BOOST_CHECK_EQUAL(string_value4,"bit1+bit2+bit3");

  bit_flag_t enum_value5 = static_cast< bit_flag_t > (bit_flag::bit1 | bit_flag::bit2);
  enum_value5 ^= bit_flag::bit2;
  ::std::string string_value5;
  ::std::stringstream stream5;
  stream5 << enum_value5;
  stream5 >> string_value5;
  BOOST_CHECK_EQUAL(string_value5,"bit1");

  bit_flag_t enum_value6 = static_cast< bit_flag_t > (0);
  ::std::string string_value6;
  ::std::stringstream stream6;
  stream6 << enum_value6;
  stream6 >> string_value6;
  BOOST_CHECK_EQUAL(string_value6,"");

  bit_flag_t enum_value7;
  ::std::string string_value7 = "";
  ::std::stringstream stream7;
  stream7 << string_value7;
  stream7 >> enum_value7;
  BOOST_CHECK_EQUAL(enum_value7,static_cast< bit_flag_t > (0));
}

BOOST_AUTO_TEST_SUITE_END()
