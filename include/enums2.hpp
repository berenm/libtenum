/**
 * @file
 * @date Apr 20, 2011
 * @todo comment
 */

#ifndef ENUMS2_HPP_
#define ENUMS2_HPP_

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>
#include <boost/lexical_cast.hpp>

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

      template< bool const IsDynamic = false, bool const IsBitFlag = false >
      static inline ::std::string serialize_impl(EnumType const enum_value_in,
                                                 ::boost::integral_constant< bool, IsDynamic > const& =
                                                     ::boost::integral_constant< bool, IsDynamic >(),
                                                 ::boost::integral_constant< bool, IsBitFlag > const& =
                                                     ::boost::integral_constant< bool, IsBitFlag >()) {
        static_assert(!IsDynamic, "serialization of dynamic enum is not supported for EnumType.");
        static_assert(!IsBitFlag, "serialization of bit flags is not supported for EnumType.");
        static_assert(IsDynamic && IsBitFlag, "serialization of enum is not supported for EnumType.");
        static_assert(!IsDynamic && !IsBitFlag, "serialization of dynamic bit flags is not supported.");
        return "";
      }

      template< bool const IsDynamic = false, bool const IsBitFlag = false >
      static inline EnumType deserialize_impl(::std::string const& value_in,
                                              ::boost::integral_constant< bool, IsDynamic > const& =
                                                  ::boost::integral_constant< bool, IsDynamic >(),
                                              ::boost::integral_constant< bool, IsBitFlag > const& =
                                                  ::boost::integral_constant< bool, IsBitFlag >()) {
        static_assert(!IsDynamic, "deserialization of dynamic enum is not supported for EnumType.");
        static_assert(!IsBitFlag, "deserialization of bit flags is not supported for EnumType.");
        static_assert(IsDynamic && IsBitFlag, "deserialization of enum is not supported for EnumType.");
        static_assert(!IsDynamic && !IsBitFlag, "deserialization of dynamic bit flags is not supported.");
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

#define LIBENUM_TUPLE_FIRST(element_m) BOOST_PP_SEQ_ELEM(0,element_m)
#define LIBENUM_TUPLE_SECOND(element_m) BOOST_PP_SEQ_ELEM(1,element_m)

#define LIBENUM_TUPLE_ELEM(element_m) LIBENUM_TUPLE_FIRST(LIBENUM_TUPLE_FIRST(element_m))
#define LIBENUM_TUPLE_VALUE(element_m) LIBENUM_TUPLE_SECOND(LIBENUM_TUPLE_FIRST(element_m))
#define LIBENUM_TUPLE_NAME(element_m) LIBENUM_TUPLE_SECOND(element_m)

#define LIBENUM_COMPLETE_VALUES(element_m) \
  BOOST_PP_IF( BOOST_PP_IS_UNARY(element_m), \
               BOOST_PP_IF( BOOST_PP_IS_UNARY(LIBENUM_TUPLE_FIRST(element_m)), \
                            BOOST_PP_IF( BOOST_PP_EQUAL(2, BOOST_PP_SEQ_SIZE(LIBENUM_TUPLE_FIRST(element_m))), \
                                         element_m, \
                                         ((LIBENUM_TUPLE_ELEM(element_m))())(LIBENUM_TUPLE_NAME(element_m)) \
                            ), \
                            ((LIBENUM_TUPLE_FIRST(element_m))(LIBENUM_TUPLE_SECOND(element_m)))(BOOST_PP_STRINGIZE(LIBENUM_TUPLE_FIRST(element_m))) \
               ), \
               ((element_m)())(BOOST_PP_STRINGIZE(element_m)) \
             )

#define LIBENUM_COMPLETE_VALUES_TRANSFORM(_,__,element_m) LIBENUM_COMPLETE_VALUES(element_m)
#define LIBENUM_COMPLETE_LIST(list_m) BOOST_PP_LIST_TRANSFORM(LIBENUM_COMPLETE_VALUES_TRANSFORM, ~, list_m)
#define LIBENUM_COMPLETE_SEQ(sequence_m) BOOST_PP_LIST_TO_SEQ(LIBENUM_COMPLETE_LIST(BOOST_PP_SEQ_TO_LIST(sequence_m)))

#define LIBENUM_ELEM(element_m) (element_m)
#define LIBENUM_ELEM_VALUE(element_m,value_m) ((element_m)(= value_m))
#define LIBENUM_ELEM_NAME(element_m,name_m) (((element_m))(name_m))
#define LIBENUM_ELEM_VALUE_NAME(element_m,value_m,name_m) (((element_m)(= value_m))(name_m))

#define LIBENUM_UINT(value_m) static_cast< ::std::uint64_t > (value_m)
#define LIBENUM_ENUM(type_m,value_m) static_cast< type_m > (value_m)

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
    type_m enum_helper< type_m >::get_base_of(type_m const value_in) { \
      switch (value_in) { \
        BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_GET_BASE_OF_EACH,type_m,values_m) \
        default: \
          return get_base_of(LIBENUM_DEC(type_m, value_in, 1)); \
      } \
    }

#define LIBENUM_DEFINE_SERIALIZE_EACH(_,type_m,value_m) \
    case type_m :: LIBENUM_TUPLE_ELEM(value_m): \
      return LIBENUM_TUPLE_NAME(value_m) ; \

#define LIBENUM_DEFINE_SERIALIZE(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< type_m >::serialize_impl< false, false >(type_m const value_in, \
                                                                        ::boost::false_type const&, \
                                                                        ::boost::false_type const&) { \
      switch (value_in) { \
        BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_SERIALIZE_EACH,type_m,values_m) \
        default: \
          return "__unknown__"; \
      } \
    }

#define LIBENUM_DEFINE_DESERIALIZE_EACH(_,type_m,value_m) \
    if (value_in == LIBENUM_TUPLE_NAME(value_m)) { \
      return type_m :: LIBENUM_TUPLE_ELEM(value_m); \
    } else \

#define LIBENUM_DEFINE_DESERIALIZE(type_m,values_m) \
    template< > \
    template< > \
    type_m enum_helper< type_m >::deserialize_impl< false, false >(::std::string const& value_in, \
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
    ::std::string enum_helper< type_m >::serialize_impl< true, false >(type_m const value_in, \
                                                                       ::boost::true_type const&, \
                                                                       ::boost::false_type const&) { \
      type_m base_value = get_base_of(value_in); \
      \
      ::std::ostringstream stream; \
      stream << serialize_impl(base_value); \
      \
      ::std::uint64_t offset = (LIBENUM_UINT(value_in) - LIBENUM_UINT(base_value)); \
      if (base_value != type_m ::__unknown__ && offset > 0) { \
        stream << "#" << offset; \
      } \
      \
      return stream.str(); \
    }

#define LIBENUM_DEFINE_DESERIALIZE_DYNAMIC(type_m,values_m) \
    template< > \
    template< > \
    type_m enum_helper< type_m >::deserialize_impl< true, false >(::std::string const& value_in, \
                                                                  ::boost::true_type const&, \
                                                                  ::boost::false_type const&) { \
      ::std::size_t separator_pos = value_in.find('#'); \
      type_m base_value = deserialize_impl(value_in.substr(0, separator_pos)); \
      \
      ::std::uint64_t offset = 0; \
      if (separator_pos != ::std::string::npos) { \
        offset = ::boost::lexical_cast< ::std::uint64_t >(value_in.substr(separator_pos + 1)); \
      } \
      \
      return LIBENUM_INC(type_m,base_value,offset); \
    }

#define LIBENUM_DEFINE_SERIALIZE_BITFLAG_EACH(_,type_m,value_m) \
    if (LIBENUM_UINT(value_in) & LIBENUM_UINT(type_m :: LIBENUM_TUPLE_ELEM(value_m))) { \
      stream << '+' << serialize_impl(type_m :: LIBENUM_TUPLE_ELEM(value_m)); \
    } \

#define LIBENUM_DEFINE_SERIALIZE_BITFLAG(type_m,values_m) \
    template< > \
    template< > \
    ::std::string enum_helper< type_m >::serialize_impl< false, true >(type_m const value_in, \
                                                                       ::boost::false_type const&, \
                                                                       ::boost::true_type const&) { \
      ::std::ostringstream stream; \
      \
      BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_SERIALIZE_BITFLAG_EACH,type_m,values_m) \
      \
      ::std::string out = stream.str(); \
      \
      return out.substr(::std::min(out.length(), static_cast< ::std::size_t > (1))); \
    }

#define LIBENUM_DEFINE_DESERIALIZE_BITFLAG(type_m,values_m) \
    template< > \
    template< > \
    type_m enum_helper< type_m >::deserialize_impl< false, true >(::std::string const& value_in, \
                                                                  ::boost::false_type const&, \
                                                                  ::boost::true_type const&) { \
      ::std::size_t separator_pos = value_in.find('+'); \
      type_m flag = deserialize_impl(value_in.substr(0, separator_pos)); \
      if (separator_pos != ::std::string::npos) { \
        type_m trailing_flags = deserialize(value_in.substr(separator_pos + 1)); \
        return LIBENUM_ENUM(type_m, LIBENUM_UINT(flag) | LIBENUM_UINT(trailing_flags)); \
      } else { \
        return flag; \
      } \
    }

#define LIBENUM_DEFINE_STREAMOP(type_m) \
    template< typename OutputStream > \
    OutputStream& operator<<(OutputStream& ostream, type_m const enum_in) { \
      ostream << ::enums::enum_helper< type_m >::serialize(enum_in); \
      return ostream; \
    } \
    \
    template< typename InputStream > \
    InputStream& operator>>(InputStream& istream, type_m& enum_out) { \
      ::std::string enum_string; \
      istream >> enum_string; \
      enum_out = ::enums::enum_helper< type_m >::deserialize(enum_string); \
      return istream; \
    } \

#ifdef BOOST_NO_SCOPED_ENUMS

#define LIBENUM_DECLARE_ENUM(type_m,values_m) \
  struct type_m { \
      enum type_m##_e { \
        __unknown__, \
        LIBENUM_DEFINE_ENUM_VALUES(values_m) \
      }; \
  }; \
  typedef type_m :: type_m##_e type_m##_t;

#else

#define LIBENUM_DECLARE_ENUM(type_m,values_m) \
  enum class type_m { \
    __unknown__, \
    LIBENUM_DEFINE_ENUM_VALUES(values_m) \
  }; \
  typedef type_m type_m##_t;

#endif /* BOOST_NO_SCOPED_ENUMS */

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
      template< > struct is_dynamic< type_m > : ::boost::true_type {}; \
      LIBENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE_DYNAMIC(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE_DYNAMIC(type_m,values_m) \
    } \
    LIBENUM_DEFINE_STREAMOP(type_m)

#define LIBENUM_BITFLAG_I(type_m,values_m) \
    LIBENUM_DECLARE_ENUM(type_m,values_m) \
    namespace enums { \
      template< > struct is_bit_flag< type_m > : ::boost::true_type {}; \
      LIBENUM_DEFINE_GET_BASE_OF(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE(type_m,values_m) \
      LIBENUM_DEFINE_SERIALIZE_BITFLAG(type_m,values_m) \
      LIBENUM_DEFINE_DESERIALIZE_BITFLAG(type_m,values_m) \
    } \
    LIBENUM_DEFINE_STREAMOP(type_m)

#define LIBENUM_STATIC_ENUM(type_m,values_m) LIBENUM_STATIC_ENUM_I(type_m,LIBENUM_COMPLETE_SEQ(values_m))
#define LIBENUM_DYNAMIC_ENUM(type_m,values_m) LIBENUM_DYNAMIC_ENUM_I(type_m,LIBENUM_COMPLETE_SEQ(values_m))
#define LIBENUM_BITFLAG(type_m,values_m) LIBENUM_BITFLAG_I(type_m,LIBENUM_COMPLETE_SEQ(values_m))

#endif /* ENUMS2_HPP_ */
