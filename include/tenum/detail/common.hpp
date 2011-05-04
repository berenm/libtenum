/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_DETAIL_COMMON_HPP_
#define TENUM_DETAIL_COMMON_HPP_

#ifndef IN_TENUM_HPP_
#  error "This header should not be included directly. Please use tenum.hpp."
#endif

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>

#define TENUM_TYPE(type_m) \
  BOOST_PP_CAT(type_m,_t)

#define TENUM_VALUE(type_m,value_m) \
  type_m :: value_m

#define TENUM_UNKNOWN_VALUE(type_m) \
  TENUM_VALUE(type_m,__unknown__)

#ifdef BOOST_NO_SCOPED_ENUMS

#  define TENUM_DECLARE_ENUM(type_m,values_m,unknown_value_m) \
  struct type_m { \
      enum BOOST_PP_CAT(type_m,_e) { \
        __unknown__ = unknown_value_m, \
        TENUM_DEFINE_ENUM_VALUES(values_m) \
      }; \
  }; \
  typedef type_m :: BOOST_PP_CAT(type_m,_e) TENUM_TYPE(type_m);

#else

#  define TENUM_DECLARE_ENUM(type_m,values_m,unknown_value_m) \
  enum class type_m { \
    __unknown__ = unknown_value_m, \
    TENUM_DEFINE_ENUM_VALUES(values_m) \
  }; \
  typedef type_m TENUM_TYPE(type_m);

#endif /* BOOST_NO_SCOPED_ENUMS */

#define BOOST_PP_SEQ_TO_LIST(sequence_m) \
  BOOST_PP_TUPLE_TO_LIST(BOOST_PP_ARRAY_SIZE(BOOST_PP_SEQ_TO_ARRAY(sequence_m)), BOOST_PP_SEQ_TO_TUPLE(sequence_m))

#define BOOST_PP_LIST_TO_SEQ(list_m) \
  BOOST_PP_TUPLE_TO_SEQ(BOOST_PP_LIST_SIZE(list_m), BOOST_PP_LIST_TO_TUPLE(list_m))

#define TENUM_TUPLE_FIRST(element_m) \
  BOOST_PP_TUPLE_ELEM(3,0,element_m)

#define TENUM_TUPLE_SECOND(element_m) \
  BOOST_PP_TUPLE_ELEM(3,1,element_m)

#define TENUM_TUPLE_THIRD(element_m) \
  BOOST_PP_TUPLE_ELEM(3,2,element_m)

#define TENUM_TUPLE_ELEM(element_m) \
  TENUM_TUPLE_FIRST(element_m)
#define TENUM_TUPLE_VALUE(element_m) \
  TENUM_TUPLE_SECOND(element_m)
#define TENUM_TUPLE_NAME(element_m) \
  TENUM_TUPLE_THIRD(element_m)

#define TENUM_COMPLETE_SIMPLE_VALUE(value_m) \
  TENUM_ELEM_I(value_m)

#define TENUM_COMPLETE_VALUES_TRANSFORM(_,__,value_m) \
  TENUM_COMPLETE_SIMPLE_VALUE(value_m)
#define TENUM_COMPLETE_SIMPLE_LIST(list_m) \
  BOOST_PP_LIST_TRANSFORM(TENUM_COMPLETE_VALUES_TRANSFORM, ~, list_m)
#define TENUM_COMPLETE_SIMPLE_SEQ(sequence_m) \
  BOOST_PP_LIST_TO_SEQ(TENUM_COMPLETE_SIMPLE_LIST(BOOST_PP_SEQ_TO_LIST(sequence_m)))

#define TENUM_ELEM_I(element_m)                           \
  (element_m,       ,#element_m)
#define TENUM_ELEM_VALUE_I(element_m,value_m)             \
  (element_m,value_m,#element_m)
#define TENUM_ELEM_NAME_I(element_m,name_m)               \
  (element_m,       ,name_m    )
#define TENUM_ELEM_VALUE_NAME_I(element_m,value_m,name_m) \
  (element_m,value_m,name_m    )

#define TENUM_ELEM(element_m)                           \
  (TENUM_ELEM_I(element_m))
#define TENUM_ELEM_VALUE(element_m,value_m)             \
  (TENUM_ELEM_VALUE_I(element_m,value_m))
#define TENUM_ELEM_NAME(element_m,name_m)               \
  (TENUM_ELEM_NAME_I(element_m,name_m))
#define TENUM_ELEM_VALUE_NAME(element_m,value_m,name_m) \
  (TENUM_ELEM_VALUE_NAME_I(element_m,value_m,name_m))

#define TENUM_DEFINE_ENUM_VALUES_EACH(_,__,value_m) \
  TENUM_TUPLE_ELEM(value_m) TENUM_TUPLE_VALUE(value_m),

#define TENUM_DEFINE_ENUM_VALUES(values_m) \
  BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_ENUM_VALUES_EACH, ~, values_m)

#endif /* TENUM_DETAIL_COMMON_HPP_ */
