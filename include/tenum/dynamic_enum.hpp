/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_DYNAMIC_ENUM_HPP_
#define TENUM_DYNAMIC_ENUM_HPP_

#include <boost/preprocessor.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/integer.hpp>

#define IN_TENUM_HPP_
#include "tenum/detail/common.hpp"
#include "tenum/detail/operator.hpp"
#include "tenum/detail/helper.hpp"
#include "tenum/detail/stream.hpp"
#undef IN_TENUM_HPP_

#include "tenum/default.hpp"
#include "tenum/static_enum.hpp"

#define TENUM_DEFINE_SERIALIZE_DYNAMIC(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< type_m##_t >::serialize_impl< true, false >(type_m##_t const value_in, \
                                                                       ::boost::true_type const&, \
                                                                       ::boost::false_type const&) { \
      type_m##_t base_value = get_base_of(value_in); \
      \
      ::std::ostringstream stream; \
      stream << serialize_impl< false, false >(base_value); \
      \
      ::boost::uint64_t offset = (TENUM_CAST_UINT(value_in) - TENUM_CAST_UINT(base_value)); \
      if (base_value != type_m ::__unknown__ && offset > 0) { \
        stream << TENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR << offset; \
      } \
      \
      return stream.str(); \
    }

#define TENUM_DEFINE_DESERIALIZE_DYNAMIC(type_m,values_m) \
    template< > \
    template< > \
    type_m##_t enum_helper< type_m##_t >::deserialize_impl< true, false >(::std::string const& value_in, \
                                                                      ::boost::true_type const&, \
                                                                      ::boost::false_type const&) { \
      ::std::size_t separator_pos = value_in.find(TENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR); \
      type_m##_t base_value = deserialize_impl< false, false >(value_in.substr(0, separator_pos)); \
      \
      ::boost::uint64_t offset = 0; \
      if (separator_pos != ::std::string::npos) { \
        offset = ::boost::lexical_cast< ::boost::uint64_t >(value_in.substr(separator_pos + 1)); \
      } \
      \
      return TENUM_ADD(type_m,base_value,offset); \
    }

#define TENUM_DYNAMIC_ENUM_I(type_m,values_m) \
    TENUM_DECLARE_ENUM(type_m,values_m) \
    TENUM_DECLARE_DYNAMIC_ENUM_OPERATORS(type_m) \
    namespace tenum { \
      template< > struct is_dynamic< type_m##_t > : ::boost::true_type {}; \
      TENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE_DYNAMIC(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE_DYNAMIC(type_m,values_m) \
    } \
    TENUM_DEFINE_STREAM_OPERATORS(type_m)

#define TENUM_DYNAMIC_ENUM(type_m,values_m) TENUM_DYNAMIC_ENUM_I(type_m,values_m)
#define TENUM_SIMPLE_DYNAMIC_ENUM(type_m,values_m) TENUM_DYNAMIC_ENUM_I(type_m,TENUM_COMPLETE_SIMPLE_SEQ(values_m))

#endif /* TENUM_DYNAMIC_ENUM_HPP_ */
