/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_SHORTCUT_HPP_
#define TENUM_SHORTCUT_HPP_

/**
 * @def TENUM_USE_SHORTCUTS
 * @brief If defined, will create shorter macros to access enum definition macros.
 */
#ifdef TENUM_USE_SHORTCUTS

#  define _lte_enum_s           TENUM_SIMPLE_STATIC_ENUM
#  define _lte_enum             TENUM_STATIC_ENUM
#  define _lte_dynamic_enum_s   TENUM_SIMPLE_DYNAMIC_ENUM
#  define _lte_dynamic_enum     TENUM_DYNAMIC_ENUM
#  define _lte_bit_flag_s       TENUM_SIMPLE_BIT_FLAG
#  define _lte_bit_flag         TENUM_BIT_FLAG

#  define _lte_e   TENUM_ELEMENT
#  define _lte_ev  TENUM_ELEMENT_VALUED
#  define _lte_en  TENUM_ELEMENT_NAMED
#  define _lte_evn TENUM_ELEMENT_VALUED_NAMED

#endif /* TENUM_USE_SHORTCUTS */

#endif /* TENUM_SHORTCUT_HPP_ */
