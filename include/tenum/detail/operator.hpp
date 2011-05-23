/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_DETAIL_OPERATOR_HPP_
#define TENUM_DETAIL_OPERATOR_HPP_

#ifndef IN_TENUM_HPP_
#  error "This header should not be included directly. Please use tenum.hpp."
#endif

#include <boost/integer.hpp>
#include <tenum/detail/type.hpp>

/**
 * @def TENUM_CAST_UINT(value_m)
 * @brief Expands to static_cast of value_m to uint64_t.
 */
#define TENUM_CAST_UINT(value_m) \
  static_cast< ::boost::uint64_t > (value_m)

/**
 * @def TENUM_CAST_ENUM(type_m,value_m)
 * @brief Expands to static_cast of value_m to enum type_m.
 */
#define TENUM_CAST_ENUM(type_m,value_m) \
  static_cast< TENUM_TYPE(type_m) > (value_m)

/**
 * @def TENUM_OPERATOR_BINARY(type_m,lhs_m,rhs_m,operator_m)
 * @brief Expands to binary operator operator_m applied to uint-casted lhs_m and rhs_m, then casted back to enum type_m.
 */
#define TENUM_OPERATOR_BINARY(type_m,lhs_m,rhs_m,operator_m) \
  TENUM_CAST_ENUM(type_m, TENUM_CAST_UINT(lhs_m) operator_m TENUM_CAST_UINT(rhs_m))

/**
 * @def TENUM_OPERATOR_ADD(type_m,lhs_m,rhs_m)
 * @brief Expands to addition operator applied to lhs_m and rhs_m.
 */
#define TENUM_OPERATOR_ADD(type_m,lhs_m,rhs_m) \
  TENUM_OPERATOR_BINARY(type_m,lhs_m,rhs_m,+)

/**
 * @def TENUM_OPERATOR_SUB(type_m,lhs_m,rhs_m)
 * @brief Expands to subtraction operator applied to lhs_m and rhs_m.
 */
#define TENUM_OPERATOR_SUB(type_m,lhs_m,rhs_m) \
  TENUM_OPERATOR_BINARY(type_m,lhs_m,rhs_m,-)

/**
 * @def TENUM_OPERATOR_BIT_OR(type_m,lhs_m,rhs_m)
 * @brief Expands to binary bitwise or operator applied to lhs_m and rhs_m.
 */
#define TENUM_OPERATOR_BIT_OR(type_m,lhs_m,rhs_m) \
  TENUM_OPERATOR_BINARY(type_m,lhs_m,rhs_m,|)

/**
 * @def TENUM_OPERATOR_BIT_AND(type_m,lhs_m,rhs_m)
 * @brief Expands to binary bitwise and operator applied to lhs_m and rhs_m.
 */
#define TENUM_OPERATOR_BIT_AND(type_m,lhs_m,rhs_m) \
  TENUM_OPERATOR_BINARY(type_m,lhs_m,rhs_m,&)

/**
 * @def TENUM_OPERATOR_BIT_XOR(type_m,lhs_m,rhs_m)
 * @brief Expands to binary bitwise xor operator applied to lhs_m and rhs_m.
 */
#define TENUM_OPERATOR_BIT_XOR(type_m,lhs_m,rhs_m) \
  TENUM_OPERATOR_BINARY(type_m,lhs_m,rhs_m,^)

/**
 * @def TENUM_DYNAMIC_ENUM_OPERATORS_DECLARATION(type_m)
 * @brief Expands to operators declaration for dynamic enum type_m (+, -, += and -=).
 *
 * Expands to nothing when scoped enums are not available as old-style enums are automatically casted to integers.
 */

/**
 * @def TENUM_DYNAMIC_ENUM_OPERATORS_DEFINITION(type_m)
 * @brief Expands to operators definition for dynamic enum type_m (+, -, += and -=).
 *
 * Expands to nothing when scoped enums are not available as old-style enums are automatically casted to integers.
 */

/**
 * @def TENUM_BIT_FLAG_OPERATORS_DECLARATION(type_m)
 * @brief Expands to operators declaration for bit flag type_m (&, |, ^, &=, |= and ^=).
 *
 * Expands to nothing when scoped enums are not available as old-style enums are automatically casted to integers.
 */

/**
 * @def TENUM_BIT_FLAG_OPERATORS_DEFINITION(type_m)
 * @brief Expands to operators definition for bit flag type_m (&, |, ^, &=, |= and ^=).
 *
 * Expands to nothing when scoped enums are not available as old-style enums are automatically casted to integers.
 */
#ifdef BOOST_NO_SCOPED_ENUMS

#  define TENUM_ENUM_OPERATORS_DECLARATION(type_m)
#  define TENUM_ENUM_OPERATORS_DEFINITION(type_m)
#  define TENUM_DYNAMIC_ENUM_OPERATORS_DECLARATION(type_m)
#  define TENUM_DYNAMIC_ENUM_OPERATORS_DEFINITION(type_m)
#  define TENUM_BIT_FLAG_OPERATORS_DECLARATION(type_m)
#  define TENUM_BIT_FLAG_OPERATORS_DEFINITION(type_m)

#else

#  define TENUM_ENUM_OPERATORS_DECLARATION(type_m) \
static inline bool operator!=(TENUM_TYPE(type_m) const& lhs_in, ::std::uint64_t const rhs_in); \
static inline bool operator==(TENUM_TYPE(type_m) const& lhs_in, ::std::uint64_t const rhs_in); \
static inline bool operator!=(::std::uint64_t const lhs_in, TENUM_TYPE(type_m) const& rhs_in); \
static inline bool operator==(::std::uint64_t const lhs_in, TENUM_TYPE(type_m) const& rhs_in);

#  define TENUM_ENUM_OPERATORS_DEFINITION(type_m) \
static inline bool operator!=(TENUM_TYPE(type_m) const& lhs_in, ::std::uint64_t const rhs_in) { \
  return TENUM_CAST_UINT(lhs_in) != TENUM_CAST_UINT(rhs_in); \
} \
static inline bool operator==(TENUM_TYPE(type_m) const& lhs_in, ::std::uint64_t const rhs_in) { \
  return !(lhs_in != rhs_in); \
} \
static inline bool operator!=(::std::uint64_t const lhs_in, TENUM_TYPE(type_m) const& rhs_in) { \
  return rhs_in != lhs_in; \
} \
static inline bool operator==(::std::uint64_t const lhs_in, TENUM_TYPE(type_m) const& rhs_in) { \
  return !(rhs_in != lhs_in); \
}

#  define TENUM_DYNAMIC_ENUM_OPERATORS_DECLARATION(type_m) \
static inline TENUM_TYPE(type_m) operator+(TENUM_TYPE(type_m) const lhs_in, ::std::uint64_t const rhs_in); \
static inline TENUM_TYPE(type_m) operator-(TENUM_TYPE(type_m) const lhs_in, ::std::uint64_t const rhs_in); \
static inline TENUM_TYPE(type_m)& operator+=(TENUM_TYPE(type_m)& lhs_in, ::std::uint64_t const rhs_in); \
static inline TENUM_TYPE(type_m)& operator-=(TENUM_TYPE(type_m)& lhs_in, ::std::uint64_t const rhs_in);

#  define TENUM_DYNAMIC_ENUM_OPERATORS_DEFINITION(type_m) \
static inline TENUM_TYPE(type_m) operator+(TENUM_TYPE(type_m) const lhs_in, ::std::uint64_t const rhs_in) { \
  return TENUM_OPERATOR_ADD(type_m,lhs_in,rhs_in); \
} \
static inline TENUM_TYPE(type_m) operator-(TENUM_TYPE(type_m) const lhs_in, ::std::uint64_t const rhs_in) { \
  return TENUM_OPERATOR_SUB(type_m,lhs_in,rhs_in); \
} \
static inline TENUM_TYPE(type_m)& operator+=(TENUM_TYPE(type_m)& lhs_in, ::std::uint64_t const rhs_in) { \
  return lhs_in = lhs_in + rhs_in; \
} \
static inline TENUM_TYPE(type_m)& operator-=(TENUM_TYPE(type_m)& lhs_in, ::std::uint64_t const rhs_in) { \
  return lhs_in = lhs_in - rhs_in; \
}

#  define TENUM_BIT_FLAG_OPERATORS_DECLARATION(type_m) \
static inline TENUM_TYPE(type_m) operator&(TENUM_TYPE(type_m) const lhs_in, TENUM_TYPE(type_m) const rhs_in); \
static inline TENUM_TYPE(type_m) operator|(TENUM_TYPE(type_m) const lhs_in, TENUM_TYPE(type_m) const rhs_in); \
static inline TENUM_TYPE(type_m) operator^(TENUM_TYPE(type_m) const lhs_in, TENUM_TYPE(type_m) const rhs_in); \
static inline TENUM_TYPE(type_m)& operator&=(TENUM_TYPE(type_m)& lhs_in, TENUM_TYPE(type_m) const rhs_in); \
static inline TENUM_TYPE(type_m)& operator|=(TENUM_TYPE(type_m)& lhs_in, TENUM_TYPE(type_m) const rhs_in); \
static inline TENUM_TYPE(type_m)& operator^=(TENUM_TYPE(type_m)& lhs_in, TENUM_TYPE(type_m) const rhs_in);

#  define TENUM_BIT_FLAG_OPERATORS_DEFINITION(type_m) \
static inline TENUM_TYPE(type_m) operator&(TENUM_TYPE(type_m) const lhs_in, TENUM_TYPE(type_m) const rhs_in) { \
  return TENUM_OPERATOR_BIT_AND(type_m,lhs_in,rhs_in); \
} \
static inline TENUM_TYPE(type_m) operator|(TENUM_TYPE(type_m) const lhs_in, TENUM_TYPE(type_m) const rhs_in) { \
  return TENUM_OPERATOR_BIT_OR(type_m,lhs_in,rhs_in); \
} \
static inline TENUM_TYPE(type_m) operator^(TENUM_TYPE(type_m) const lhs_in, TENUM_TYPE(type_m) const rhs_in) { \
  return TENUM_OPERATOR_BIT_XOR(type_m,lhs_in,rhs_in); \
} \
static inline TENUM_TYPE(type_m)& operator&=(TENUM_TYPE(type_m)& lhs_in, TENUM_TYPE(type_m) const rhs_in) { \
  return lhs_in = lhs_in & rhs_in; \
} \
static inline TENUM_TYPE(type_m)& operator|=(TENUM_TYPE(type_m)& lhs_in, TENUM_TYPE(type_m) const rhs_in) { \
  return lhs_in = lhs_in | rhs_in; \
} \
static inline TENUM_TYPE(type_m)& operator^=(TENUM_TYPE(type_m)& lhs_in, TENUM_TYPE(type_m) const rhs_in) { \
  return lhs_in = lhs_in ^ rhs_in; \
}

#endif /* BOOST_NO_SCOPED_ENUMS */

#endif /* TENUM_DETAIL_OPERATOR_HPP_ */
