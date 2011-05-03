/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_DEFAULT_HPP_
#define TENUM_DEFAULT_HPP_

/**
 * @def TENUM_DEFAULT_NAME(type_m,name_m)
 * @brief Defines the way an enum name will be serialized, expands to a char const*.
 *
 * Default serialization is simply "name_m", unless TENUM_DEFAULT_NAME_EXPLICIT_TYPE is defined, in which case, the
 * serialization is "type_m::name_m".
 *
 * @param type_m [in] the type of the enum, as a type name.
 * @param name_m [in] the name of the enum value, as a char const*.
 */
#ifndef TENUM_DEFAULT_NAME
#  ifdef TENUM_DEFAULT_NAME_EXPLICIT_TYPE
#    define TENUM_DEFAULT_NAME(type_m,name_m) #type_m "::" name_m
#  else /* TENUM_DEFAULT_NAME_EXPLICIT_TYPE */
#    define TENUM_DEFAULT_NAME(type_m,name_m) name_m
#  endif /* TENUM_DEFAULT_NAME_EXPLICIT_TYPE */
#endif /* TENUM_DEFAULT_NAME */

/**
 * @def TENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR
 * @brief Defines the default separator for dynamic enums offsets, expands to char or char const*.
 *
 * Default separator is '#', which will serialize dynamic enums as "enum_value#offset".
 *
 * @warning The separator should not include any space (or related) character.
 */
#ifndef TENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR
#  define TENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR '#'
#endif /* TENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR */

/**
 * @def TENUM_DEFAULT_BIT_FLAG_SEPARATOR
 * @brief Defines the default separator for bit flags combination, expands to char or char const*.
 *
 * Default separator is '+', which will serialize bit flags as "enum_value1+enum_value2".
 *
 * @warning The separator should not include any space (or related) character.
 */
#ifndef TENUM_DEFAULT_BIT_FLAG_SEPARATOR
#  define TENUM_DEFAULT_BIT_FLAG_SEPARATOR '+'
#endif /* TENUM_DEFAULT_BIT_FLAG_SEPARATOR */

#endif /* TENUM_DEFAULT_HPP_ */
