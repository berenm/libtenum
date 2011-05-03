/**
 * @file
 * @date May 3, 2011
 */

#ifndef TENUM_DETAIL_OPERATOR_HPP_
#define TENUM_DETAIL_OPERATOR_HPP_

#ifndef IN_TENUM_HPP_
#  error "This header should not be included directly. Please use tenum.hpp."
#endif

#include <boost/config.hpp>
#include <boost/integer.hpp>

#define TENUM_CAST_UINT(value_m)              static_cast< ::boost::uint64_t > (value_m)
#define TENUM_CAST_ENUM(type_m,value_m)       static_cast< type_m##_t > (value_m)

#define TENUM_BINARY_OPERATOR(type_m,lhs_m,rhs_m,operator_m) TENUM_CAST_ENUM(type_m, TENUM_CAST_UINT(lhs_m) operator_m TENUM_CAST_UINT(rhs_m))

#define TENUM_ADD(type_m,lhs_m,rhs_m) TENUM_BINARY_OPERATOR(type_m,lhs_m,rhs_m,+)
#define TENUM_SUB(type_m,lhs_m,rhs_m) TENUM_BINARY_OPERATOR(type_m,lhs_m,rhs_m,-)

#define TENUM_INC(type_m,value_m) TENUM_ADD(type_m,value_m,1)
#define TENUM_DEC(type_m,value_m) TENUM_SUB(type_m,value_m,1)

#define TENUM_BIT_OR(type_m,lhs_m,rhs_m) TENUM_BINARY_OPERATOR(type_m,lhs_m,rhs_m,|)
#define TENUM_BIT_AND(type_m,lhs_m,rhs_m) TENUM_BINARY_OPERATOR(type_m,lhs_m,rhs_m,&)
#define TENUM_BIT_XOR(type_m,lhs_m,rhs_m) TENUM_BINARY_OPERATOR(type_m,lhs_m,rhs_m,^)

#ifdef BOOST_NO_SCOPED_ENUMS

#  define TENUM_DECLARE_DYNAMIC_ENUM_OPERATORS(type_m)
#  define TENUM_DECLARE_BIT_FLAG_OPERATORS(type_m)

#else

#  define TENUM_DECLARE_DYNAMIC_ENUM_OPERATORS(type_m) \
          static inline type_m operator+(type_m const lhs_in, ::std::uint64_t const rhs_in) { \
            return TENUM_ADD(type_m,lhs_in,rhs_in); \
          } \
          static inline type_m operator-(type_m const lhs_in, ::std::uint64_t const rhs_in) { \
            return TENUM_SUB(type_m,lhs_in,rhs_in); \
          }

#  define TENUM_DECLARE_BIT_FLAG_OPERATORS(type_m) \
          static inline type_m operator&(type_m const lhs_in, type_m const rhs_in) { \
            return TENUM_BIT_AND(type_m,lhs_in,rhs_in); \
          } \
          static inline type_m operator|(type_m const lhs_in, type_m const rhs_in) { \
            return TENUM_BIT_OR(type_m,lhs_in,rhs_in); \
          } \
          static inline type_m operator^(type_m const lhs_in, type_m const rhs_in) { \
            return TENUM_BIT_XOR(type_m,lhs_in,rhs_in); \
          } \
          static inline type_m& operator&=(type_m& lhs_in, type_m const rhs_in) { \
            lhs_in = lhs_in & rhs_in; \
            return lhs_in; \
          } \
          static inline type_m& operator|=(type_m& lhs_in, type_m const rhs_in) { \
            lhs_in = lhs_in | rhs_in; \
            return lhs_in; \
          } \
          static inline type_m& operator^=(type_m& lhs_in, type_m const rhs_in) { \
            lhs_in = lhs_in ^ rhs_in; \
            return lhs_in; \
          } \

#endif /* BOOST_NO_SCOPED_ENUMS */

#endif /* TENUM_DETAIL_OPERATOR_HPP_ */
