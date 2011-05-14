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

/**
 * @def TENUM_TYPE(type_m)
 * @brief Expands to the typename that should be used when manipulating type_m enum variables, parameters or template
 * typenames.
 * @param type_m the enum typename.
 */
#define TENUM_TYPE(type_m) \
  BOOST_PP_CAT(type_m,_t)

/**
 * @def TENUM_VALUE(type_m,value_m)
 * @brief Expands to the type_m enum value value_m.
 * @param type_m the enum typename.
 * @param value_m the defined enum value.
 */
#define TENUM_VALUE(type_m,value_m) \
  type_m :: value_m

/**
 * @def TENUM_VALUE_UNKNOWN(type_m)
 * @brief Expands to the type_m defined "unknown" enum value.
 * @param type_m the enum typename.
 */
#define TENUM_VALUE_UNKNOWN(type_m) \
  TENUM_VALUE(type_m,lte_unknown)

#endif /* TENUM_DETAIL_COMMON_HPP_ */
