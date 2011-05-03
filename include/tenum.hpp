/**
 * @file
 * @date Apr 20, 2011
 */

#ifndef TENUM_HPP_
#define TENUM_HPP_

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/integer.hpp>

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

/**
 * @brief Elementary macros.
 */
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
#  define TENUM_DECLARE_ENUM(type_m,values_m) \
          struct type_m { \
              enum type_m##_e { \
                __unknown__ = -1, \
                TENUM_DEFINE_ENUM_VALUES(values_m) \
              }; \
          }; \
          typedef type_m :: type_m##_e type_m##_t;

#  define TENUM_DECLARE_DYNAMIC_ENUM_OPERATORS(type_m)
#  define TENUM_DECLARE_BIT_FLAG_OPERATORS(type_m)

#else
#  define TENUM_DECLARE_ENUM(type_m,values_m) \
          enum class type_m { \
            __unknown__ = -1, \
            TENUM_DEFINE_ENUM_VALUES(values_m) \
          }; \
          typedef type_m type_m##_t;

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

namespace tenum {

  template< typename EnumType >
  struct is_dynamic: ::boost::false_type {
  };

  template< typename EnumType >
  struct is_bit_flag: ::boost::false_type {
  };

  template< typename EnumType >
  struct enum_helper {
      static inline EnumType get_base_of(EnumType const value_in);

      template< bool const IsDynamic, bool const IsBitFlag >
      static inline ::std::string serialize_impl(EnumType const enum_value_in,
                                                 ::boost::integral_constant< bool, IsDynamic > const& = ::boost::integral_constant<
                                                     bool, IsDynamic >(),
                                                 ::boost::integral_constant< bool, IsBitFlag > const& = ::boost::integral_constant<
                                                     bool, IsBitFlag >()) {
        BOOST_STATIC_ASSERT_MSG(!IsDynamic, "serialization of dynamic enum is not supported for EnumType.");
        BOOST_STATIC_ASSERT_MSG(!IsBitFlag, "serialization of bit flags is not supported for EnumType.");
        BOOST_STATIC_ASSERT_MSG(IsDynamic && IsBitFlag, "serialization of enum is not supported for EnumType.");
        BOOST_STATIC_ASSERT_MSG(!IsDynamic && !IsBitFlag, "serialization of dynamic bit flags is not supported.");
        return "";
      }

      template< bool const IsDynamic, bool const IsBitFlag >
      static inline EnumType deserialize_impl(::std::string const& value_in,
                                              ::boost::integral_constant< bool, IsDynamic > const& = ::boost::integral_constant<
                                                  bool, IsDynamic >(),
                                              ::boost::integral_constant< bool, IsBitFlag > const& = ::boost::integral_constant<
                                                  bool, IsBitFlag >()) {
        BOOST_STATIC_ASSERT_MSG(!IsDynamic, "deserialization of dynamic enum is not supported for EnumType.");
        BOOST_STATIC_ASSERT_MSG(!IsBitFlag, "deserialization of bit flags is not supported for EnumType.");
        BOOST_STATIC_ASSERT_MSG(IsDynamic && IsBitFlag, "deserialization of enum is not supported for EnumType.");
        BOOST_STATIC_ASSERT_MSG(!IsDynamic && !IsBitFlag, "deserialization of dynamic bit flags is not supported.");
        return static_cast< EnumType > (0);
      }

      static inline ::std::string serialize(EnumType const value_in) {
        return serialize_impl(value_in, is_dynamic< EnumType > (), is_bit_flag< EnumType > ());
      }

      static inline EnumType deserialize(::std::string const& value_in) {
        return deserialize_impl(value_in, is_dynamic< EnumType > (), is_bit_flag< EnumType > ());
      }
  };

} // namespace tenum


#define BOOST_PP_SEQ_TO_LIST(sequence_m) BOOST_PP_TUPLE_TO_LIST(BOOST_PP_ARRAY_SIZE(BOOST_PP_SEQ_TO_ARRAY(sequence_m)), BOOST_PP_SEQ_TO_TUPLE(sequence_m))
#define BOOST_PP_LIST_TO_SEQ(list_m) BOOST_PP_TUPLE_TO_SEQ(BOOST_PP_LIST_SIZE(list_m), BOOST_PP_LIST_TO_TUPLE(list_m))

#define TENUM_TUPLE_FIRST(element_m) BOOST_PP_TUPLE_ELEM(3,0,element_m)
#define TENUM_TUPLE_SECOND(element_m) BOOST_PP_TUPLE_ELEM(3,1,element_m)
#define TENUM_TUPLE_THIRD(element_m) BOOST_PP_TUPLE_ELEM(3,2,element_m)

#define TENUM_TUPLE_ELEM(element_m) TENUM_TUPLE_FIRST(element_m)
#define TENUM_TUPLE_VALUE(element_m) TENUM_TUPLE_SECOND(element_m)
#define TENUM_TUPLE_NAME(element_m) TENUM_TUPLE_THIRD(element_m)

#define TENUM_COMPLETE_SIMPLE_VALUE(value_m) TENUM_ELEM_I(value_m)

#define TENUM_COMPLETE_VALUES_TRANSFORM(_,__,value_m) TENUM_COMPLETE_SIMPLE_VALUE(value_m)
#define TENUM_COMPLETE_SIMPLE_LIST(list_m) BOOST_PP_LIST_TRANSFORM(TENUM_COMPLETE_VALUES_TRANSFORM, ~, list_m)
#define TENUM_COMPLETE_SIMPLE_SEQ(sequence_m) BOOST_PP_LIST_TO_SEQ(TENUM_COMPLETE_SIMPLE_LIST(BOOST_PP_SEQ_TO_LIST(sequence_m)))

#define TENUM_ELEM_I(element_m)                           (element_m,       ,#element_m)
#define TENUM_ELEM_VALUE_I(element_m,value_m)             (element_m,value_m,#element_m)
#define TENUM_ELEM_NAME_I(element_m,name_m)               (element_m,       ,name_m    )
#define TENUM_ELEM_VALUE_NAME_I(element_m,value_m,name_m) (element_m,value_m,name_m    )

#define TENUM_ELEM(element_m)                           (TENUM_ELEM_I(element_m))
#define TENUM_ELEM_VALUE(element_m,value_m)             (TENUM_ELEM_VALUE_I(element_m,value_m))
#define TENUM_ELEM_NAME(element_m,name_m)               (TENUM_ELEM_NAME_I(element_m,name_m))
#define TENUM_ELEM_VALUE_NAME(element_m,value_m,name_m) (TENUM_ELEM_VALUE_NAME_I(element_m,value_m,name_m))

#define TENUM_DEFINE_ENUM_VALUES_EACH(_,__,value_m) \
    TENUM_TUPLE_ELEM(value_m) TENUM_TUPLE_VALUE(value_m),

#define TENUM_DEFINE_ENUM_VALUES(values_m) BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_ENUM_VALUES_EACH, ~, values_m)

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

#define TENUM_DEFINE_SERIALIZE_DYNAMIC(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< type_m##_t >::serialize_impl< true, false >(type_m##_t const value_in, \
                                                                       ::boost::true_type const&, \
                                                                       ::boost::false_type const&) { \
      type_m##_t base_value = get_base_of(value_in); \
      \
      ::std::ostringstream stream; \
      stream << serialize_impl< false, false >(base_value); \
      \
      ::boost::uint64_t offset = (TENUM_CAST_UINT(value_in) - TENUM_CAST_UINT(base_value)); \
      if (base_value != type_m ::__unknown__ && offset > 0) { \
        stream << TENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR << offset; \
      } \
      \
      return stream.str(); \
    }

#define TENUM_DEFINE_DESERIALIZE_DYNAMIC(type_m,values_m) \
    template< > \
    template< > \
    type_m##_t enum_helper< type_m##_t >::deserialize_impl< true, false >(::std::string const& value_in, \
                                                                      ::boost::true_type const&, \
                                                                      ::boost::false_type const&) { \
      ::std::size_t separator_pos = value_in.find(TENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR); \
      type_m##_t base_value = deserialize_impl< false, false >(value_in.substr(0, separator_pos)); \
      \
      ::boost::uint64_t offset = 0; \
      if (separator_pos != ::std::string::npos) { \
        offset = ::boost::lexical_cast< ::boost::uint64_t >(value_in.substr(separator_pos + 1)); \
      } \
      \
      return TENUM_ADD(type_m,base_value,offset); \
    }

#define TENUM_DEFINE_SERIALIZE_BIT_FLAG_EACH(_,type_m,value_m) \
    if (TENUM_CAST_UINT(value_in) & TENUM_CAST_UINT(type_m :: TENUM_TUPLE_ELEM(value_m))) { \
      stream << TENUM_DEFAULT_BIT_FLAG_SEPARATOR << serialize_impl< false, false >(type_m :: TENUM_TUPLE_ELEM(value_m)); \
    } \

#define TENUM_DEFINE_SERIALIZE_BIT_FLAG(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< type_m##_t >::serialize_impl< false, true >(type_m##_t const value_in, \
                                                                       ::boost::false_type const&, \
                                                                       ::boost::true_type const&) { \
      ::std::ostringstream stream; \
      \
      BOOST_PP_SEQ_FOR_EACH(TENUM_DEFINE_SERIALIZE_BIT_FLAG_EACH,type_m,values_m) \
      \
      ::std::string out = stream.str(); \
      \
      return out.substr(::std::min(out.length(), static_cast< ::std::size_t > (1))); \
    }

#define TENUM_DEFINE_DESERIALIZE_BIT_FLAG(type_m,values_m) \
    template< > \
    template< > \
    type_m##_t enum_helper< type_m##_t >::deserialize_impl< false, true >(::std::string const& value_in, \
                                                                      ::boost::false_type const&, \
                                                                      ::boost::true_type const&) { \
      ::std::size_t separator_pos = value_in.find(TENUM_DEFAULT_BIT_FLAG_SEPARATOR); \
      type_m##_t flag = deserialize_impl< false, false >(value_in.substr(0, separator_pos)); \
      if (separator_pos != ::std::string::npos) { \
        type_m##_t trailing_flags = deserialize(value_in.substr(separator_pos + 1)); \
        return TENUM_CAST_ENUM(type_m, TENUM_CAST_UINT(flag) | TENUM_CAST_UINT(trailing_flags)); \
      } else { \
        return flag; \
      } \
    }

#define TENUM_DEFINE_STREAMOP(type_m) \
    template< typename OutputStream > \
    OutputStream& operator<<(OutputStream& ostream, type_m##_t const enum_in) { \
      ostream << ::tenum::enum_helper< type_m##_t >::serialize(enum_in); \
      return ostream; \
    } \
    \
    template< typename InputStream > \
    InputStream& operator>>(InputStream& istream, type_m##_t& enum_out) { \
      ::std::string enum_string; \
      istream >> enum_string; \
      enum_out = ::tenum::enum_helper< type_m##_t >::deserialize(enum_string); \
      return istream; \
    }

#define TENUM_STATIC_ENUM_I(type_m,values_m) \
    TENUM_DECLARE_ENUM(type_m,values_m) \
    namespace tenum { \
      TENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
    } \
    TENUM_DEFINE_STREAMOP(type_m)

#define TENUM_DYNAMIC_ENUM_I(type_m,values_m) \
    TENUM_DECLARE_ENUM(type_m,values_m) \
    TENUM_DECLARE_DYNAMIC_ENUM_OPERATORS(type_m) \
    namespace tenum { \
      template< > struct is_dynamic< type_m##_t > : ::boost::true_type {}; \
      TENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE_DYNAMIC(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE_DYNAMIC(type_m,values_m) \
    } \
    TENUM_DEFINE_STREAMOP(type_m)

#define TENUM_BIT_FLAG_I(type_m,values_m) \
    TENUM_DECLARE_ENUM(type_m,values_m) \
    TENUM_DECLARE_BIT_FLAG_OPERATORS(type_m) \
    namespace tenum { \
      template< > struct is_bit_flag< type_m##_t > : ::boost::true_type {}; \
      TENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE(type_m,values_m) \
      TENUM_DEFINE_SERIALIZE_BIT_FLAG(type_m,values_m) \
      TENUM_DEFINE_DESERIALIZE_BIT_FLAG(type_m,values_m) \
    } \
    TENUM_DEFINE_STREAMOP(type_m)

#define TENUM_STATIC_ENUM(type_m,values_m) TENUM_STATIC_ENUM_I(type_m,values_m)
#define TENUM_DYNAMIC_ENUM(type_m,values_m) TENUM_DYNAMIC_ENUM_I(type_m,values_m)
#define TENUM_BIT_FLAG(type_m,values_m) TENUM_BIT_FLAG_I(type_m,values_m)

#define TENUM_SIMPLE_STATIC_ENUM(type_m,values_m) TENUM_STATIC_ENUM_I(type_m,TENUM_COMPLETE_SIMPLE_SEQ(values_m))
#define TENUM_SIMPLE_DYNAMIC_ENUM(type_m,values_m) TENUM_DYNAMIC_ENUM_I(type_m,TENUM_COMPLETE_SIMPLE_SEQ(values_m))
#define TENUM_SIMPLE_BIT_FLAG(type_m,values_m) TENUM_BIT_FLAG_I(type_m,TENUM_COMPLETE_SIMPLE_SEQ(values_m))

#endif /* TENUM_HPP_ */
