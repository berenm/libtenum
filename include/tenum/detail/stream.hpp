/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_DETAIL_STREAM_HPP_
#define TENUM_DETAIL_STREAM_HPP_

#ifndef IN_TENUM_HPP_
#  error "This header should not be included directly. Please use tenum.hpp."
#endif

#include <tenum/detail/helper.hpp>

#define TENUM_STREAM_OPERATORS_DECLARATION(type_m) \
template< typename OutputStream > \
static inline OutputStream& operator<<(OutputStream& ostream, TENUM_TYPE(type_m) const enum_in); \
template< typename InputStream > \
static inline InputStream& operator>>(InputStream& istream, TENUM_TYPE(type_m)& enum_out);

/**
 * @def TENUM_STREAM_OPERATORS_DEFINITION(type_m)
 * @brief Expands to templated stream operator definition for the type_m enum.
 *
 * The stream operators use ::tenum::enum_helper (de)serialize methods to convert type_m enum to string and
 * string to type_m enum. The input stream operator uses a temporary string to store the enum value, and will
 * read the content of the stream up to the first white space character in this string before converting it to
 * type_m enum. Therefore, serialized enum values should never contain white spaces.
 */
#define TENUM_STREAM_OPERATORS_DEFINITION(type_m) \
template< typename OutputStream > \
static inline OutputStream& operator<<(OutputStream& ostream, TENUM_TYPE(type_m) const enum_in) { \
  ostream << ::tenum::enum_helper< TENUM_TYPE(type_m) >::serialize(enum_in); \
  return ostream; \
} \
\
template< typename InputStream > \
static inline InputStream& operator>>(InputStream& istream, TENUM_TYPE(type_m)& enum_out) { \
  ::std::string enum_string; \
  istream >> enum_string; \
  enum_out = ::tenum::enum_helper< TENUM_TYPE(type_m) >::deserialize(enum_string); \
  return istream; \
}

#endif /* TENUM_DETAIL_STREAM_HPP_ */
