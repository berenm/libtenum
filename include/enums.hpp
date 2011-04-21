/**
 * @file
 * @date Apr 20, 2011
 * @todo comment
 */

#ifndef ENUMS_HPP_
#define ENUMS_HPP_

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/integer.hpp>

#ifndef LIBENUM_DEFAULT_NAME
#  ifdef LIBENUM_DEFAULT_NAME_EXPLICIT_TYPE
#    define LIBENUM_DEFAULT_NAME(type_m,name_m) #type_m "::" name_m
#  else /* LIBENUM_DEFAULT_NAME_EXPLICIT_TYPE */
#    define LIBENUM_DEFAULT_NAME(type_m,name_m) name_m
#  endif /* LIBENUM_DEFAULT_NAME_EXPLICIT_TYPE */
#endif /* LIBENUM_DEFAULT_NAME */

#ifndef LIBENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR
#  define LIBENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR '#'
#endif /* LIBENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR */

#ifndef LIBENUM_DEFAULT_BIT_FLAG_SEPARATOR
#  define LIBENUM_DEFAULT_BIT_FLAG_SEPARATOR '+'
#endif /* LIBENUM_DEFAULT_BIT_FLAG_SEPARATOR */

#ifdef LIBENUM_USE_SHORTCUTS
#  define _enum_s LIBENUM_SIMPLE_STATIC_ENUM
#  define _enum LIBENUM_STATIC_ENUM
#  define _dynamic_enum_s LIBENUM_SIMPLE_DYNAMIC_ENUM
#  define _dynamic_enum LIBENUM_DYNAMIC_ENUM
#  define _bit_flag_s LIBENUM_SIMPLE_BIT_FLAG
#  define _bit_flag LIBENUM_BIT_FLAG

#  define _ LIBENUM_ELEM
#  define _v LIBENUM_ELEM_VALUE
#  define _n LIBENUM_ELEM_NAME
#  define _vn LIBENUM_ELEM_VALUE_NAME
#endif /* LIBENUM_USE_SHORTCUTS */

#ifdef BOOST_NO_SCOPED_ENUMS
#  define LIBENUM_DECLARE_ENUM(type_m,values_m) \
          struct type_m { \
              enum type_m##_e { \
                __unknown__, \
                LIBENUM_DEFINE_ENUM_VALUES(values_m) \
              }; \
          }; \
          typedef type_m :: type_m##_e type_m##_t;

#else
#  define LIBENUM_DECLARE_ENUM(type_m,values_m) \
          enum class type_m { \
            __unknown__, \
            LIBENUM_DEFINE_ENUM_VALUES(values_m) \
          }; \
          typedef type_m type_m##_t;

#endif /* BOOST_NO_SCOPED_ENUMS */

namespace enums {

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

} // namespace enums


#define BOOST_PP_SEQ_TO_LIST(sequence_m) BOOST_PP_TUPLE_TO_LIST(BOOST_PP_ARRAY_SIZE(BOOST_PP_SEQ_TO_ARRAY(sequence_m)), BOOST_PP_SEQ_TO_TUPLE(sequence_m))
#define BOOST_PP_LIST_TO_SEQ(list_m) BOOST_PP_TUPLE_TO_SEQ(BOOST_PP_LIST_SIZE(list_m), BOOST_PP_LIST_TO_TUPLE(list_m))

#define LIBENUM_TUPLE_FIRST(element_m) BOOST_PP_TUPLE_ELEM(3,0,element_m)
#define LIBENUM_TUPLE_SECOND(element_m) BOOST_PP_TUPLE_ELEM(3,1,element_m)
#define LIBENUM_TUPLE_THIRD(element_m) BOOST_PP_TUPLE_ELEM(3,2,element_m)

#define LIBENUM_TUPLE_ELEM(element_m) LIBENUM_TUPLE_FIRST(element_m)
#define LIBENUM_TUPLE_VALUE(element_m) LIBENUM_TUPLE_SECOND(element_m)
#define LIBENUM_TUPLE_NAME(element_m) LIBENUM_TUPLE_THIRD(element_m)

#define LIBENUM_COMPLETE_SIMPLE_VALUE(value_m) LIBENUM_ELEM_I(value_m)

#define LIBENUM_COMPLETE_VALUES_TRANSFORM(_,__,value_m) LIBENUM_COMPLETE_SIMPLE_VALUE(value_m)
#define LIBENUM_COMPLETE_SIMPLE_LIST(list_m) BOOST_PP_LIST_TRANSFORM(LIBENUM_COMPLETE_VALUES_TRANSFORM, ~, list_m)
#define LIBENUM_COMPLETE_SIMPLE_SEQ(sequence_m) BOOST_PP_LIST_TO_SEQ(LIBENUM_COMPLETE_SIMPLE_LIST(BOOST_PP_SEQ_TO_LIST(sequence_m)))

#define LIBENUM_ELEM_I(element_m)                           (element_m,       ,#element_m)
#define LIBENUM_ELEM_VALUE_I(element_m,value_m)             (element_m,value_m,#element_m)
#define LIBENUM_ELEM_NAME_I(element_m,name_m)               (element_m,       ,name_m    )
#define LIBENUM_ELEM_VALUE_NAME_I(element_m,value_m,name_m) (element_m,value_m,name_m    )

#define LIBENUM_ELEM(element_m)                           (LIBENUM_ELEM_I(element_m))
#define LIBENUM_ELEM_VALUE(element_m,value_m)             (LIBENUM_ELEM_VALUE_I(element_m,value_m))
#define LIBENUM_ELEM_NAME(element_m,name_m)               (LIBENUM_ELEM_NAME_I(element_m,name_m))
#define LIBENUM_ELEM_VALUE_NAME(element_m,value_m,name_m) (LIBENUM_ELEM_VALUE_NAME_I(element_m,value_m,name_m))

#define LIBENUM_UINT(value_m) static_cast< ::boost::uint64_t > (value_m)
#define LIBENUM_ENUM(type_m,value_m) static_cast< type_m##_t > (value_m)

#define LIBENUM_DEC(type_m,value_m,amount_m) LIBENUM_ENUM(type_m, LIBENUM_UINT(value_m) - LIBENUM_UINT(amount_m))
#define LIBENUM_INC(type_m,value_m,amount_m) LIBENUM_ENUM(type_m, LIBENUM_UINT(value_m) + LIBENUM_UINT(amount_m))

#define LIBENUM_DEFINE_ENUM_VALUES_EACH(_,__,value_m) \
    LIBENUM_TUPLE_ELEM(value_m) LIBENUM_TUPLE_VALUE(value_m),

#define LIBENUM_DEFINE_ENUM_VALUES(values_m) BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_ENUM_VALUES_EACH, ~, values_m)

#define LIBENUM_DEFINE_GET_BASE_OF_EACH(_,type_m,value_m) \
    case type_m :: LIBENUM_TUPLE_ELEM(value_m): \
      return type_m :: LIBENUM_TUPLE_ELEM(value_m); \

#define LIBENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
    template< > \
    type_m##_t enum_helper< type_m##_t >::get_base_of(type_m##_t const value_in) { \
      switch (value_in) { \
        BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_GET_BASE_OF_EACH,type_m,values_m) \
        default: \
          return get_base_of(LIBENUM_DEC(type_m, value_in, 1)); \
      } \
    }

#define LIBENUM_DEFINE_SERIALIZE_EACH(_,type_m,value_m) \
    case type_m :: LIBENUM_TUPLE_ELEM(value_m): \
      return LIBENUM_DEFAULT_NAME(type_m,LIBENUM_TUPLE_NAME(value_m)) ; \

#define LIBENUM_DEFINE_SERIALIZE(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< type_m##_t >::serialize_impl< false, false >(type_m##_t const value_in, \
                                                                        ::boost::false_type const&, \
                                                                        ::boost::false_type const&) { \
      switch (value_in) { \
        BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_SERIALIZE_EACH,type_m,values_m) \
        default: \
          return LIBENUM_DEFAULT_NAME(type_m,"__unknown__"); \
      } \
    }

#define LIBENUM_DEFINE_DESERIALIZE_EACH(_,type_m,value_m) \
    if (value_in == LIBENUM_DEFAULT_NAME(type_m,LIBENUM_TUPLE_NAME(value_m))) { \
      return type_m :: LIBENUM_TUPLE_ELEM(value_m); \
    } else \

#define LIBENUM_DEFINE_DESERIALIZE(type_m,values_m) \
    template< > \
    template< > \
    type_m##_t enum_helper< type_m##_t >::deserialize_impl< false, false >(::std::string const& value_in, \
                                                                       ::boost::false_type const&, \
                                                                       ::boost::false_type const&) { \
      BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_DESERIALIZE_EACH,type_m,values_m) \
      { \
        return type_m ::__unknown__; \
      } \
    } \

#define LIBENUM_DEFINE_SERIALIZE_DYNAMIC(type_m,values_m) \
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
      ::boost::uint64_t offset = (LIBENUM_UINT(value_in) - LIBENUM_UINT(base_value)); \
      if (base_value != type_m ::__unknown__ && offset > 0) { \
        stream << LIBENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR << offset; \
      } \
      \
      return stream.str(); \
    }

#define LIBENUM_DEFINE_DESERIALIZE_DYNAMIC(type_m,values_m) \
    template< > \
    template< > \
    type_m##_t enum_helper< type_m##_t >::deserialize_impl< true, false >(::std::string const& value_in, \
                                                                      ::boost::true_type const&, \
                                                                      ::boost::false_type const&) { \
      ::std::size_t separator_pos = value_in.find(LIBENUM_DEFAULT_DYNAMIC_ENUM_SEPARATOR); \
      type_m##_t base_value = deserialize_impl< false, false >(value_in.substr(0, separator_pos)); \
      \
      ::boost::uint64_t offset = 0; \
      if (separator_pos != ::std::string::npos) { \
        offset = ::boost::lexical_cast< ::boost::uint64_t >(value_in.substr(separator_pos + 1)); \
      } \
      \
      return LIBENUM_INC(type_m,base_value,offset); \
    }

#define LIBENUM_DEFINE_SERIALIZE_BIT_FLAG_EACH(_,type_m,value_m) \
    if (LIBENUM_UINT(value_in) & LIBENUM_UINT(type_m :: LIBENUM_TUPLE_ELEM(value_m))) { \
      stream << LIBENUM_DEFAULT_BIT_FLAG_SEPARATOR << serialize_impl< false, false >(type_m :: LIBENUM_TUPLE_ELEM(value_m)); \
    } \

#define LIBENUM_DEFINE_SERIALIZE_BIT_FLAG(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< type_m##_t >::serialize_impl< false, true >(type_m##_t const value_in, \
                                                                       ::boost::false_type const&, \
                                                                       ::boost::true_type const&) { \
      ::std::ostringstream stream; \
      \
      BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_SERIALIZE_BIT_FLAG_EACH,type_m,values_m) \
      \
      ::std::string out = stream.str(); \
      \
      return out.substr(::std::min(out.length(), static_cast< ::std::size_t > (1))); \
    }

#define LIBENUM_DEFINE_DESERIALIZE_BIT_FLAG(type_m,values_m) \
    template< > \
    template< > \
    type_m##_t enum_helper< type_m##_t >::deserialize_impl< false, true >(::std::string const& value_in, \
                                                                      ::boost::false_type const&, \
                                                                      ::boost::true_type const&) { \
      ::std::size_t separator_pos = value_in.find(LIBENUM_DEFAULT_BIT_FLAG_SEPARATOR); \
      type_m##_t flag = deserialize_impl< false, false >(value_in.substr(0, separator_pos)); \
      if (separator_pos != ::std::string::npos) { \
        type_m##_t trailing_flags = deserialize(value_in.substr(separator_pos + 1)); \
        return LIBENUM_ENUM(type_m, LIBENUM_UINT(flag) | LIBENUM_UINT(trailing_flags)); \
      } else { \
        return flag; \
      } \
    }

#define LIBENUM_DEFINE_STREAMOP(type_m) \
    template< typename OutputStream > \
    OutputStream& operator<<(OutputStream& ostream, type_m##_t const enum_in) { \
      ostream << ::enums::enum_helper< type_m##_t >::serialize(enum_in); \
      return ostream; \
    } \
    \
    template< typename InputStream > \
    InputStream& operator>>(InputStream& istream, type_m##_t& enum_out) { \
      ::std::string enum_string; \
      istream >> enum_string; \
      enum_out = ::enums::enum_helper< type_m##_t >::deserialize(enum_string); \
      return istream; \
    } \

#define LIBENUM_STATIC_ENUM_I(type_m,values_m) \
    LIBENUM_DECLARE_ENUM(type_m,values_m) \
    namespace enums { \
      LIBENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE(type_m,values_m) \
    } \
    LIBENUM_DEFINE_STREAMOP(type_m)

#define LIBENUM_DYNAMIC_ENUM_I(type_m,values_m) \
    LIBENUM_DECLARE_ENUM(type_m,values_m) \
    namespace enums { \
      template< > struct is_dynamic< type_m##_t > : ::boost::true_type {}; \
      LIBENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE_DYNAMIC(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE_DYNAMIC(type_m,values_m) \
    } \
    LIBENUM_DEFINE_STREAMOP(type_m)

#define LIBENUM_BIT_FLAG_I(type_m,values_m) \
    LIBENUM_DECLARE_ENUM(type_m,values_m) \
    namespace enums { \
      template< > struct is_bit_flag< type_m##_t > : ::boost::true_type {}; \
      LIBENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE_BIT_FLAG(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE_BIT_FLAG(type_m,values_m) \
    } \
    LIBENUM_DEFINE_STREAMOP(type_m)

#define LIBENUM_STATIC_ENUM(type_m,values_m) LIBENUM_STATIC_ENUM_I(type_m,values_m)
#define LIBENUM_DYNAMIC_ENUM(type_m,values_m) LIBENUM_DYNAMIC_ENUM_I(type_m,values_m)
#define LIBENUM_BIT_FLAG(type_m,values_m) LIBENUM_BIT_FLAG_I(type_m,values_m)

#define LIBENUM_SIMPLE_STATIC_ENUM(type_m,values_m) LIBENUM_STATIC_ENUM_I(type_m,LIBENUM_COMPLETE_SIMPLE_SEQ(values_m))
#define LIBENUM_SIMPLE_DYNAMIC_ENUM(type_m,values_m) LIBENUM_DYNAMIC_ENUM_I(type_m,LIBENUM_COMPLETE_SIMPLE_SEQ(values_m))
#define LIBENUM_SIMPLE_BIT_FLAG(type_m,values_m) LIBENUM_BIT_FLAG_I(type_m,LIBENUM_COMPLETE_SIMPLE_SEQ(values_m))

#endif /* ENUMS_HPP_ */
