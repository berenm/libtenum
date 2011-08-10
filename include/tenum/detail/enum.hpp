/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_DETAIL_ENUM_HPP_
#define TENUM_DETAIL_ENUM_HPP_

#ifndef IN_TENUM_HPP_
#  error "This header should not be included directly. Please use tenum.hpp."
#endif

#include <tenum/detail/type.hpp>

/**
 * @def TENUM_TUPLE_CREATE(value_m,integer_value_m,name_m)
 * @brief Expands to an element of a values sequence, as a tuple of 3 elements.
 *
 * First element of the tuple is the defined enum value, second element is the defined enum value's initial integer value
 * preceded by = or empty if the default enum integer value should be used, third element is the serialized name of the
 * enum value, as a char const*.
 */
#define TENUM_TUPLE_CREATE(value_m,integer_value_m,name_m) \
  (value_m,integer_value_m,name_m)

/**
 * @def TENUM_TUPLE_GET_VALUE(tuple_m)
 * @brief Expands to the defined enum value of tuple_m.
 */
#define TENUM_TUPLE_GET_VALUE(tuple_m) \
  BOOST_PP_TUPLE_ELEM(3,0,tuple_m)

/**
 * @def TENUM_TUPLE_GET_INTEGER_VALUE(tuple_m)
 * @brief Expands to the integer value tuple_m, or empty.
 */
#define TENUM_TUPLE_GET_INTEGER_VALUE(tuple_m) \
  BOOST_PP_TUPLE_ELEM(3,1,tuple_m)

/**
 * @def TENUM_TUPLE_GET_NAME(tuple_m)
 * @brief Expands to the serialized name of tuple_m.
 */
#define TENUM_TUPLE_GET_NAME(tuple_m) \
  BOOST_PP_TUPLE_ELEM(3,2,tuple_m)

/**
 * @def TENUM_TUPLE(value_m)
 * @brief Expands to a tenum tuple, using only the value_m information to create it.
 *
 * The integer value is set to empty, so the default enum integer value is used, and the serialized name is set to
 * the stringized name of value_m.
 */
#define TENUM_TUPLE(value_m) \
  TENUM_TUPLE_CREATE(value_m,BOOST_PP_EMPTY(),BOOST_PP_STRINGIZE(value_m))

/**
 * @def TENUM_TUPLE_VALUED(value_m,integer_value_m)
 * @brief Expands to a tenum tuple, using the value_m and the given explicit integer value integer_value_m to create it.
 *
 * The serialized name is set to the stringized name of value_m.
 */
#define TENUM_TUPLE_VALUED(value_m,integer_value_m) \
  TENUM_TUPLE_CREATE(value_m,=integer_value_m,BOOST_PP_STRINGIZE(value_m))

/**
 * @def TENUM_TUPLE_NAMED(value_m,name_m)
 * @brief Expands to a tenum tuple, using the value_m and the given explicit serialized name name_m to create it.
 *
 * The integer value is set to empty, so the default enum integer value is used.
 */
#define TENUM_TUPLE_NAMED(value_m,name_m) \
  TENUM_TUPLE_CREATE(value_m,BOOST_PP_EMPTY(),name_m)

/**
 * @def TENUM_TUPLE_VALUED_NAMED(value_m,integer_value_m,name_m)
 * @brief Expands to a tenum tuple, using the value_m, the given explicit integer value integer_value_m and the given
 * explicit serialized name name_m to create it.
 */
#define TENUM_TUPLE_VALUED_NAMED(value_m,integer_value_m,name_m) \
  TENUM_TUPLE_CREATE(value_m,=integer_value_m,name_m)

/**
 * @def TENUM_ELEMENT(value_m)
 * @brief Expands to a sequence element containing the a tenum tuple created using TENUM_TUPLE(value_m).
 */
#define TENUM_ELEMENT(value_m) \
  (TENUM_TUPLE(value_m))

/**
 * @def TENUM_ELEMENT_VALUED(value_m,integer_value_m)
 * @brief Expands to a sequence element containing the a tenum tuple created using TENUM_TUPLE_VALUED(value_m,integer_value_m).
 */
#define TENUM_ELEMENT_VALUED(value_m,integer_value_m) \
  (TENUM_TUPLE_VALUED(value_m,integer_value_m))

/**
 * @def TENUM_ELEMENT_NAMED(value_m,name_m)
 * @brief Expands to a sequence element containing the a tenum tuple created using TENUM_TUPLE_NAMED(value_m,name_m).
 */
#define TENUM_ELEMENT_NAMED(value_m,name_m) \
  (TENUM_TUPLE_NAMED(value_m,name_m))

/**
 * @def TENUM_ELEMENT_VALUED_NAMED(value_m,integer_value_m,name_m)
 * @brief Expands to a sequence element containing the a tenum tuple created using TENUM_TUPLE_VALUED_NAMED(value_m,integer_value_m,name_m).
 */
#define TENUM_ELEMENT_VALUED_NAMED(value_m,integer_value_m,name_m) \
  (TENUM_TUPLE_VALUED_NAMED(value_m,integer_value_m,name_m))

#define TENUM_ENUM_VALUES_COMPLETE_EACH(_1,_2,value_m) \
  TENUM_TUPLE(value_m)
#define TENUM_ENUM_VALUES_COMPLETE(values_m) \
  BOOST_PP_SEQ_TRANSFORM(TENUM_ENUM_VALUES_COMPLETE_EACH, ~, values_m)

#define TENUM_ENUM_VALUES_DEFINITION_EACH(_1,_2,tuple_m) \
  TENUM_TUPLE_GET_VALUE(tuple_m) TENUM_TUPLE_GET_INTEGER_VALUE(tuple_m),
#define TENUM_ENUM_VALUES_DEFINITION(tuples_m) \
  BOOST_PP_SEQ_FOR_EACH(TENUM_ENUM_VALUES_DEFINITION_EACH, ~, tuples_m)

/**
 * @def TENUM_ENUM_DEFINITION(type_m,tuples_m,unknown_integer_value_m)
 * @brief Expands to the declaration of type_m enum, with or without enum class keyword depending on the availability
 * of it, and using a trick otherwise.
 *
 * This will define two typenames, type_m, which should be used to access the enum defined values, and
 * TENUM_TYPE(type_m) which should be used to type variables, parameters or templates typenames.
 *
 * An additional lte_unknown value will be added before the given values list, using the integer value
 * unknown_integer_value_m, which should be lower or greater than all other values defined in the enum:
 * - -1 is the default lte_unknown integer value for static and dynamic enums.
 * - 0 is the default lte_unknown integer value for bit flags.
 *
 * @param type_m the enum typename.
 * @param tuples_m the defined values of the enum, as a boost preprocessor sequence of tenum tuples.
 * @param unknown_integer_value_m the integer value of the lte_unknown value.
 */

#ifdef BOOST_NO_SCOPED_ENUMS

#  define TENUM_ENUM_DEFINITION(type_m,tuples_m) \
struct type_m { \
    enum BOOST_PP_CAT(type_m,_e) : ::boost::uint64_t { \
      TENUM_ENUM_VALUES_DEFINITION(tuples_m) \
    }; \
}; \
typedef type_m :: BOOST_PP_CAT(type_m,_e) TENUM_TYPE(type_m);

#else

#  define TENUM_ENUM_DEFINITION(type_m,tuples_m) \
enum class type_m : ::boost::uint64_t { \
  TENUM_ENUM_VALUES_DEFINITION(tuples_m) \
}; \
typedef type_m TENUM_TYPE(type_m);

#endif /* BOOST_NO_SCOPED_ENUMS */

#endif /* TENUM_DETAIL_ENUM_HPP_ */
