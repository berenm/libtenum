/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_STATIC_ENUM_HPP_
#define TENUM_STATIC_ENUM_HPP_

#define IN_TENUM_HPP_
#include <tenum/detail/enum.hpp>
#include <tenum/detail/operator.hpp>
#include <tenum/detail/stream.hpp>
#undef IN_TENUM_HPP_

#include <tenum/default.hpp>

#define TENUM_GET_BASE_OF_DEFINITION_EACH(_,type_m,value_m) \
  case TENUM_VALUE(type_m,TENUM_TUPLE_GET_ELEM(value_m)): \
    return TENUM_VALUE(type_m,TENUM_TUPLE_GET_ELEM(value_m)); \

#define TENUM_GET_BASE_OF_DEFINITION(type_m,values_m) \
  template< > \
  inline TENUM_TYPE(type_m) \
  enum_helper< TENUM_TYPE(type_m) >::get_base_of(TENUM_TYPE(type_m) const value_in) { \
    switch (value_in) { \
      BOOST_PP_SEQ_FOR_EACH(TENUM_GET_BASE_OF_DEFINITION_EACH,type_m,values_m) \
      case TENUM_VALUE_UNKNOWN(type_m): \
        return TENUM_VALUE_UNKNOWN(type_m); \
      default: \
        return get_base_of(TENUM_OPERATOR_SUB(type_m,value_in,1)); \
    } \
  }

#define TENUM_DEFINE_SERIALIZE_EACH(_,type_m,value_m) \
  case TENUM_VALUE(type_m,TENUM_TUPLE_GET_ELEM(value_m)): \
    return TENUM_DEFAULT_NAME(type_m,TENUM_TUPLE_GET_NAME(value_m)) ; \

#define TENUM_DEFINE_SERIALIZE(type_m,values_m) \
  template< > \
  template< > \
  inline ::std::string \
  enum_helper< TENUM_TYPE(type_m) >::serialize_impl< false, false >(TENUM_TYPE(type_m) const value_in, \
                                                                    ::boost::false_type const&, \
                                                                    ::boost::false_type const&) { \
    switch (value_in) { \
      BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_SERIALIZE_EACH,type_m,values_m) \
      default: \
        return TENUM_DEFAULT_NAME(type_m,"__unknown__"); \
    } \
  }

#define TENUM_DEFINE_DESERIALIZE_EACH(_,type_m,value_m) \
  if (value_in == TENUM_DEFAULT_NAME(type_m,TENUM_TUPLE_GET_NAME(value_m))) { \
    return TENUM_VALUE(type_m,TENUM_TUPLE_GET_ELEM(value_m)); \
  } else \

#define TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
  template< > \
  template< > \
  inline TENUM_TYPE(type_m) \
  enum_helper< TENUM_TYPE(type_m) >::deserialize_impl< false, false >(::std::string const& value_in, \
                                                                      ::boost::false_type const&, \
                                                                      ::boost::false_type const&) { \
    BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_DESERIALIZE_EACH,type_m,values_m) \
    { \
      return TENUM_VALUE_UNKNOWN(type_m); \
    } \
  }

#define TENUM_DECLARE_STATIC_ENUM_SERIALIZATION(type_m,values_m) \
  namespace tenum { \
    TENUM_GET_BASE_OF_DEFINITION(type_m,values_m) \
    TENUM_DEFINE_SERIALIZE(type_m,values_m) \
    TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
  } \
  TENUM_STREAM_OPERATORS_DEFINITION(type_m)

#define TENUM_DECLARE_STATIC_ENUM(type_m,values_m) \
  TENUM_ENUM_DEFINITION(type_m,values_m,-1)

#define TENUM_STATIC_ENUM_I(type_m,values_m) \
  TENUM_DECLARE_STATIC_ENUM(type_m,values_m) \
  TENUM_DECLARE_STATIC_ENUM_SERIALIZATION(type_m,values_m)

#define TENUM_STATIC_ENUM(type_m,values_m) \
  TENUM_STATIC_ENUM_I(type_m,values_m)
#define TENUM_SIMPLE_STATIC_ENUM(type_m,values_m) \
  TENUM_STATIC_ENUM_I(type_m,TENUM_ENUM_VALUES_COMPLETE(values_m))

#endif /* TENUM_STATIC_ENUM_HPP_ */
