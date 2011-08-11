/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#define TENUM_USE_SHORTCUTS 1
#include "tenum.hpp"

#define BOOST_TEST_MODULE tenum_bit_field_tests
#include <boost/test/unit_test.hpp>

lte_bit_field(bit_field,
    lte_ev(bit1,0b0001)
    lte_ev(bit2,0b0010)
    lte_ev(bit3,0b0100)
    lte_evn(bit4,0b1000,"last_bit"),
    ::boost::uint16_t
)

/**
 * @defgroup bit_field_tests Bit fields test cases
 */
BOOST_AUTO_TEST_SUITE(bit_field_tests)

/**
 * @class test_bit_field_from_or_serialization
 * @brief Tests bit field construction from '|' operator and serialization.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_from_or_serialization) {
  bit_field_t enum_value = static_cast< bit_field_t > (bit_field::bit1 | bit_field::bit2);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit1+bit2");
}

/**
 * @class test_bit_field_serialization_explicit
 * @brief Tests bit field serialization with an explicit string equivalent.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_serialization_explicit) {
  bit_field_t enum_value = static_cast< bit_field_t > (bit_field::bit2 | bit_field::bit4);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit2+last_bit");
}

/**
 * @class test_bit_field_from_int_serialization
 * @brief Tests bit field construction from integer and serialization.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_from_int_serialization) {
  bit_field_t enum_value = static_cast< bit_field_t > (0b110);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit2+bit3");
}

/**
 * @class test_bit_field_deserialization
 * @brief Tests bit field deserialization and comparison.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_deserialization) {
  bit_field_t enum_value;
  ::std::string string_value = "bit1+bit3";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< bit_field_t > (bit_field::bit1 | bit_field::bit3));
  BOOST_CHECK_EQUAL(enum_value,static_cast< bit_field_t > (0b101));
}

/**
 * @class test_bit_field_or_variable
 * @brief Tests bit field '|' operator between Bit field variable and constants and serialization.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_or_variable) {
  bit_field_t enum_value = static_cast< bit_field_t > (bit_field::bit1 | bit_field::bit2);
  enum_value = static_cast< bit_field_t > (enum_value | bit_field::bit3);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit1+bit2+bit3");
}

/**
 * @class test_bit_field_xor_variable
 * @brief Tests bit field '^' operator between Bit field variable and constants and serialization.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_xor_variable) {
  bit_field_t enum_value = static_cast< bit_field_t > (bit_field::bit1 | bit_field::bit2);
  enum_value = static_cast< bit_field_t > (enum_value ^ bit_field::bit2);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"bit1");
}

/**
 * @class test_bit_field_empty_serialization
 * @brief Tests empty Bit field serialization.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_empty_serialization) {
  bit_field_t enum_value = static_cast< bit_field_t > (0);
  ::std::string string_value;
  ::std::stringstream stream;
  stream << enum_value;
  stream >> string_value;
  BOOST_CHECK_EQUAL(string_value,"");
}

/**
 * @class test_bit_field_empty_deserialization
 * @brief Tests empty Bit field deserialization.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_empty_deserialization) {
  bit_field_t enum_value;
  ::std::string string_value = "";
  ::std::stringstream stream;
  stream << string_value;
  stream >> enum_value;
  BOOST_CHECK_EQUAL(enum_value,static_cast< bit_field_t > (0));
}

/**
 * @class test_bit_field_integers_eq
 * @brief Tests bit field integer equality operator.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_integers_eq) {
  bit_field_t enum_value = bit_field::bit2;
  ::boost::uint64_t integer_value = 2;
  BOOST_CHECK(integer_value == enum_value);
  BOOST_CHECK(enum_value == integer_value);
}

/**
 * @class test_bit_field_integers_neq
 * @brief Tests bit field integer inequality operator.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_integers_neq) {
  bit_field_t enum_value = bit_field::bit2;
  ::boost::uint64_t integer_value = 0;
  BOOST_CHECK(integer_value != enum_value);
  BOOST_CHECK(enum_value != integer_value);
}

/**
 * @class test_bit_field_integers_bitwise_and
 * @brief Tests integer bitwise and operator with bit field.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_integers_bitwise_and) {
  bit_field_t enum_value = bit_field::bit2;
  ::boost::uint64_t integer_value1 = 0b011 & enum_value;
  BOOST_CHECK(integer_value1 == 0b010);
  ::boost::uint64_t integer_value2 = enum_value & 0b011;
  BOOST_CHECK(integer_value2 == 0b010);
}

/**
 * @class test_bit_field_integers_bitwise_or
 * @brief Tests integer bitwise or operator with bit field.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_integers_bitwise_or) {
  bit_field_t enum_value = bit_field::bit2;
  ::boost::uint64_t integer_value1 = 0b001 | enum_value;
  BOOST_CHECK(integer_value1 == 0b011);
  ::boost::uint64_t integer_value2 = enum_value | 0b001;
  BOOST_CHECK(integer_value2 == 0b011);
}

/**
 * @class test_bit_field_integers_bitwise_xor
 * @brief Tests integer bitwise xor operator with bit field.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_integers_bitwise_xor) {
  bit_field_t enum_value = bit_field::bit2;
  ::boost::uint64_t integer_value1 = 0b011 ^ enum_value;
  BOOST_CHECK(integer_value1 == 0b001);
  ::boost::uint64_t integer_value2 = enum_value ^ 0b011;
  BOOST_CHECK(integer_value2 == 0b001);
}

/**
 * @class test_bit_field_integers_bitwise_and_assign
 * @brief Tests integer bitwise and assination operator with bit field.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_integers_bitwise_and_assign) {
  bit_field_t enum_value = bit_field::bit2;
  ::boost::uint64_t integer_value = 0b011;
  integer_value &= enum_value;
  BOOST_CHECK(integer_value == 0b010);
}

/**
 * @class test_bit_field_integers_bitwise_or_assign
 * @brief Tests integer bitwise or assination operator with bit field.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_integers_bitwise_or_assign) {
  bit_field_t enum_value = bit_field::bit2;
  ::boost::uint64_t integer_value = 0b001;
  integer_value |= enum_value;
  BOOST_CHECK(integer_value == 0b011);
}

/**
 * @class test_bit_field_integers_bitwise_xor_assign
 * @brief Tests integer bitwise xor assination operator with bit field.
 * @ingroup bit_field_tests
 */
BOOST_AUTO_TEST_CASE(test_bit_field_integers_bitwise_xor_assign) {
  bit_field_t enum_value = bit_field::bit2;
  ::boost::uint64_t integer_value = 0b011;
  integer_value ^= enum_value;
  BOOST_CHECK(integer_value == 0b001);
}

BOOST_AUTO_TEST_SUITE_END()
