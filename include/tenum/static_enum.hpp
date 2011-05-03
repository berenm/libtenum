/**
 * @file
 * @date May 3, 2011
 */

#ifndef TENUM_STATIC_ENUM_HPP_
#define TENUM_STATIC_ENUM_HPP_

#include <boost/preprocessor.hpp>

#define IN_TENUM_HPP_
#include "tenum/detail/common.hpp"
#include "tenum/detail/operator.hpp"
#include "tenum/detail/helper.hpp"
#include "tenum/detail/stream.hpp"
#undef IN_TENUM_HPP_

#include "tenum/default.hpp"

#define TENUM_DEFINE_GET_BASE_OF_EACH(_,type_m,value_m) \
    case type_m :: TENUM_TUPLE_ELEM(value_m): \
      return type_m :: TENUM_TUPLE_ELEM(value_m); \

#define TENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
    template< > \
    type_m##_t enum_helper< type_m##_t >::get_base_of(type_m##_t const value_in) { \
      switch (value_in) { \
        BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_GET_BASE_OF_EACH,type_m,values_m) \
        case type_m :: __unknown__: \
          return type_m :: __unknown__; \
        default: \
          return get_base_of(TENUM_DEC(type_m,value_in)); \
      } \
    }

#define TENUM_DEFINE_SERIALIZE_EACH(_,type_m,value_m) \
    case type_m :: TENUM_TUPLE_ELEM(value_m): \
      return TENUM_DEFAULT_NAME(type_m,TENUM_TUPLE_NAME(value_m)) ; \

#define TENUM_DEFINE_SERIALIZE(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< type_m##_t >::serialize_impl< false, false >(type_m##_t const value_in, \
                                                                        ::boost::false_type const&, \
                                                                        ::boost::false_type const&) { \
      switch (value_in) { \
        BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_SERIALIZE_EACH,type_m,values_m) \
        default: \
          return TENUM_DEFAULT_NAME(type_m,"__unknown__"); \
      } \
    }

#define TENUM_DEFINE_DESERIALIZE_EACH(_,type_m,value_m) \
    if (value_in == TENUM_DEFAULT_NAME(type_m,TENUM_TUPLE_NAME(value_m))) { \
      return type_m :: TENUM_TUPLE_ELEM(value_m); \
    } else \

#define TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
    template< > \
    template< > \
    type_m##_t enum_helper< type_m##_t >::deserialize_impl< false, false >(::std::string const& value_in, \
                                                                       ::boost::false_type const&, \
                                                                       ::boost::false_type const&) { \
      BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_DESERIALIZE_EACH,type_m,values_m) \
      { \
        return type_m ::__unknown__; \
      } \
    } \

#define TENUM_STATIC_ENUM_I(type_m,values_m) \
    TENUM_DECLARE_ENUM(type_m,values_m) \
    namespace tenum { \
      TENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
    } \
    TENUM_DEFINE_STREAM_OPERATORS(type_m)

#define TENUM_STATIC_ENUM(type_m,values_m) TENUM_STATIC_ENUM_I(type_m,values_m)
#define TENUM_SIMPLE_STATIC_ENUM(type_m,values_m) TENUM_STATIC_ENUM_I(type_m,TENUM_COMPLETE_SIMPLE_SEQ(values_m))

#endif /* TENUM_STATIC_ENUM_HPP_ */
