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

#include "tenum/detail/helper.hpp"

#define TENUM_DEFINE_STREAM_OPERATORS(type_m) \
    template< typename OutputStream > \
    OutputStream& operator<<(OutputStream& ostream, type_m##_t const enum_in) { \
      ostream << ::tenum::enum_helper< type_m##_t >::serialize(enum_in); \
      return ostream; \
    } \
    \
    template< typename InputStream > \
    InputStream& operator>>(InputStream& istream, type_m##_t& enum_out) { \
      ::std::string enum_string; \
      istream >> enum_string; \
      enum_out = ::tenum::enum_helper< type_m##_t >::deserialize(enum_string); \
      return istream; \
    }

#endif /* TENUM_DETAIL_STREAM_HPP_ */
