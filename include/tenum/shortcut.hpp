/**
 * @file
 * @date May 3, 2011
 */

#ifndef TENUM_SHORTCUT_HPP_
#define TENUM_SHORTCUT_HPP_

/**
 * @def TENUM_USE_SHORTCUTS
 * @brief If defined, will create shorter macros to access enum definition macros.
 */
#ifdef TENUM_USE_SHORTCUTS
#  define _e_enum_s TENUM_SIMPLE_STATIC_ENUM
#  define _e_enum TENUM_STATIC_ENUM
#  define _e_dynamic_enum_s TENUM_SIMPLE_DYNAMIC_ENUM
#  define _e_dynamic_enum TENUM_DYNAMIC_ENUM
#  define _e_bit_flag_s TENUM_SIMPLE_BIT_FLAG
#  define _e_bit_flag TENUM_BIT_FLAG

#  define _e_ TENUM_ELEM
#  define _e_v TENUM_ELEM_VALUE
#  define _e_n TENUM_ELEM_NAME
#  define _e_vn TENUM_ELEM_VALUE_NAME

#  define _e_add TENUM_ADD
#  define _e_sub TENUM_SUB

#  define _e_inc TENUM_INC
#  define _e_dec TENUM_DEC

#  define _e_bit_or TENUM_BIT_OR
#  define _e_bit_and TENUM_BIT_AND

#  define _e_cast_uint TENUM_CAST_UINT
#  define _e_cast_enum TENUM_CAST_ENUM
#endif /* TENUM_USE_SHORTCUTS */

#endif /* TENUM_SHORTCUT_HPP_ */
