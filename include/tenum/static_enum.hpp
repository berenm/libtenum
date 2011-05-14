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

/**
 * @def TENUM_GET_BASE_OF_DEFINITION_EACH(_,type_m,tuple_m)
 * @brief Expands to a single case statement returning the same enum value as the tested case.
 */
#define TENUM_GET_BASE_OF_DEFINITION_EACH(_,type_m,tuple_m) \
  if(TENUM_CAST_UINT(value_in) >= TENUM_CAST_UINT(TENUM_VALUE(type_m,TENUM_TUPLE_GET_VALUE(tuple_m)))) { \
    return TENUM_VALUE(type_m,TENUM_TUPLE_GET_VALUE(tuple_m)); \
  } else \

#define TENUM_GET_BASE_OF_DEFINITION(type_m,tuples_m) \
  template< > \
  inline TENUM_TYPE(type_m) \
  enum_helper< TENUM_TYPE(type_m) >::get_base_of(TENUM_TYPE(type_m) const value_in) { \
    if(TENUM_CAST_UINT(value_in) == TENUM_CAST_UINT(TENUM_VALUE_UNKNOWN(type_m))) { \
      return TENUM_VALUE_UNKNOWN(type_m); \
    } \
    BOOST_PP_SEQ_FOR_EACH(TENUM_GET_BASE_OF_DEFINITION_EACH,type_m,BOOST_PP_SEQ_REVERSE(tuples_m)) { \
      return TENUM_VALUE_UNKNOWN(type_m); \
    } \
  }

#define TENUM_DEFINE_SERIALIZE_EACH(_,type_m,tuple_m) \
  case TENUM_VALUE(type_m,TENUM_TUPLE_GET_VALUE(tuple_m)): \
    return TENUM_DEFAULT_NAME(type_m,TENUM_TUPLE_GET_NAME(tuple_m)) ; \

#define TENUM_DEFINE_SERIALIZE(type_m,tuples_m) \
  template< > \
  template< > \
  inline ::std::string \
  enum_helper< TENUM_TYPE(type_m) >::serialize_impl< false, false >(TENUM_TYPE(type_m) const value_in, \
                                                                    ::boost::false_type const&, \
                                                                    ::boost::false_type const&) { \
    switch (value_in) { \
      BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_SERIALIZE_EACH,type_m,tuples_m) \
      default: \
        return TENUM_DEFAULT_NAME(type_m,"lte_unknown"); \
    } \
  }

#define TENUM_DEFINE_DESERIALIZE_EACH(_,type_m,tuple_m) \
  if (value_in == TENUM_DEFAULT_NAME(type_m,TENUM_TUPLE_GET_NAME(tuple_m))) { \
    return TENUM_VALUE(type_m,TENUM_TUPLE_GET_VALUE(tuple_m)); \
  } else \

#define TENUM_DEFINE_DESERIALIZE(type_m,tuples_m) \
  template< > \
  template< > \
  inline TENUM_TYPE(type_m) \
  enum_helper< TENUM_TYPE(type_m) >::deserialize_impl< false, false >(::std::string const& value_in, \
                                                                      ::boost::false_type const&, \
                                                                      ::boost::false_type const&) { \
    BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_DESERIALIZE_EACH,type_m,tuples_m) \
    { \
      return TENUM_VALUE_UNKNOWN(type_m); \
    } \
  }

#define TENUM_DECLARE_STATIC_ENUM_SERIALIZATION(type_m,tuples_m) \
  namespace tenum { \
    TENUM_GET_BASE_OF_DEFINITION(type_m,tuples_m) \
    TENUM_DEFINE_SERIALIZE(type_m,tuples_m) \
    TENUM_DEFINE_DESERIALIZE(type_m,tuples_m) \
  } \
  TENUM_STREAM_OPERATORS_DEFINITION(type_m)

#define TENUM_DECLARE_STATIC_ENUM(type_m,tuples_m) \
  TENUM_ENUM_DEFINITION(type_m,tuples_m,-1)

#define TENUM_STATIC_ENUM_I(type_m,tuples_m) \
  TENUM_DECLARE_STATIC_ENUM(type_m,tuples_m) \
  TENUM_DECLARE_STATIC_ENUM_SERIALIZATION(type_m,tuples_m)

#define TENUM_STATIC_ENUM(type_m,tuples_m) \
  TENUM_STATIC_ENUM_I(type_m,tuples_m)
#define TENUM_SIMPLE_STATIC_ENUM(type_m,values_m) \
  TENUM_STATIC_ENUM_I(type_m,TENUM_ENUM_VALUES_COMPLETE(values_m))

#endif /* TENUM_STATIC_ENUM_HPP_ */
