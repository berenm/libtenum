/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_BIT_FLAG_HPP_
#define TENUM_BIT_FLAG_HPP_

#include <boost/preprocessor.hpp>

#define IN_TENUM_HPP_
#include "tenum/detail/common.hpp"
#include "tenum/detail/operator.hpp"
#include "tenum/detail/helper.hpp"
#include "tenum/detail/stream.hpp"
#undef IN_TENUM_HPP_

#include "tenum/default.hpp"
#include "tenum/static_enum.hpp"

#define TENUM_DEFINE_SERIALIZE_BIT_FLAG_EACH(_,type_m,value_m) \
    if (TENUM_CAST_UINT(value_in) & TENUM_CAST_UINT(type_m :: TENUM_TUPLE_ELEM(value_m))) { \
      stream << TENUM_DEFAULT_BIT_FLAG_SEPARATOR << serialize_impl< false, false >(type_m :: TENUM_TUPLE_ELEM(value_m)); \
    }

#define TENUM_DEFINE_SERIALIZE_BIT_FLAG(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< BOOST_PP_CAT(type_m,_t) >::serialize_impl< false, true >(BOOST_PP_CAT(type_m,_t) const value_in, \
                                                                                    ::boost::false_type const&, \
                                                                                    ::boost::true_type const&) { \
      ::std::ostringstream stream; \
      \
      BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_SERIALIZE_BIT_FLAG_EACH,type_m,values_m) \
      \
      ::std::string out = stream.str(); \
      \
      return out.substr(::std::min(out.length(), static_cast< ::std::size_t > (1))); \
    }

#define TENUM_DEFINE_DESERIALIZE_BIT_FLAG(type_m,values_m) \
    template< > \
    template< > \
    BOOST_PP_CAT(type_m,_t) enum_helper< BOOST_PP_CAT(type_m,_t) >::deserialize_impl< false, true >(::std::string const& value_in, \
                                                                                   ::boost::false_type const&, \
                                                                                   ::boost::true_type const&) { \
      ::std::size_t separator_pos = value_in.find(TENUM_DEFAULT_BIT_FLAG_SEPARATOR); \
      BOOST_PP_CAT(type_m,_t) flag = deserialize_impl< false, false >(value_in.substr(0, separator_pos)); \
      if (separator_pos != ::std::string::npos) { \
        BOOST_PP_CAT(type_m,_t) trailing_flags = deserialize(value_in.substr(separator_pos + 1)); \
        return TENUM_CAST_ENUM(type_m, TENUM_CAST_UINT(flag) | TENUM_CAST_UINT(trailing_flags)); \
      } else { \
        return flag; \
      } \
    }

#define TENUM_DECLARE_BIT_FLAG_SERIALIZATION(type_m,values_m) \
    namespace tenum { \
      template< > struct is_bit_flag< BOOST_PP_CAT(type_m,_t) > : ::boost::true_type {}; \
      TENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE_BIT_FLAG(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE_BIT_FLAG(type_m,values_m) \
    } \
    TENUM_DEFINE_STREAM_OPERATORS(type_m)

#define TENUM_DECLARE_BIT_FLAG(type_m,values_m) \
    TENUM_DECLARE_ENUM(type_m,values_m) \
    TENUM_DECLARE_BIT_FLAG_OPERATORS(type_m)

#define TENUM_BIT_FLAG_I(type_m,values_m) \
    TENUM_DECLARE_BIT_FLAG(type_m,values_m) \
    TENUM_DECLARE_BIT_FLAG_SERIALIZATION(type_m,values_m)

#define TENUM_BIT_FLAG(type_m,values_m) TENUM_BIT_FLAG_I(type_m,values_m)
#define TENUM_SIMPLE_BIT_FLAG(type_m,values_m) TENUM_BIT_FLAG_I(type_m,TENUM_COMPLETE_SIMPLE_SEQ(values_m))

#endif /* TENUM_BIT_FLAG_HPP_ */
