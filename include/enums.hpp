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

#ifdef BOOST_NO_SCOPED_ENUMS

#define LIBENUM_DECLARE_ENUM(type_m,values_m) \
  struct type_m { \
      enum type_m##_e { \
        __unknown__, \
        values_m \
      }; \
  }; \
  typedef type_m :: type_m##_e type_m##_t;

#else

#define LIBENUM_DECLARE_ENUM(type_m,values_m) \
  enum class type_m { \
    __unknown__, \
    values_m, \
    __last__ \
  }; \
  typedef type_m type_m##_t;

#endif /* BOOST_NO_SCOPED_ENUMS */

#define LIBENUM_UINT(value_m) static_cast< ::std::uint64_t > (value_m)
#define LIBENUM_ENUM(type_m,value_m) static_cast< type_m > (value_m)

#define LIBENUM_DEC(type_m,value_m,amount_m) LIBENUM_ENUM(type_m, LIBENUM_UINT(value_m) - LIBENUM_UINT(amount_m))
#define LIBENUM_INC(type_m,value_m,amount_m) LIBENUM_ENUM(type_m, LIBENUM_UINT(value_m) + LIBENUM_UINT(amount_m))

#define LIBENUM_PREV(type_m,value_m) LIBENUM_DEC(type_m, type_m :: value_m, 1)
#define LIBENUM_NEXT(type_m,value_m) LIBENUM_INC(type_m, type_m :: value_m, 1)

namespace enums {
  template< typename EnumType, EnumType const EnumValue = EnumType::__unknown__ >
  struct serializer {
      static ::std::string serialize(EnumType const enum_value_in,
                                     EnumType const base_value_in,
                                     ::std::string const& base_string_in) {
        if (enum_value_in == EnumValue) {
          ::std::ostringstream stream;
          stream << base_string_in;
          if (base_value_in != EnumType::__unknown__) {
            stream << "+" << LIBENUM_UINT(LIBENUM_DEC(EnumType, EnumValue, base_value_in)) << " ";
          }
          return stream.str();
        } else {
          return serializer< EnumType, LIBENUM_INC(EnumType, EnumValue, 1) >::serialize(enum_value_in,
                                                                                        base_value_in,
                                                                                        base_string_in);
        }
      }
  };

  template< typename EnumType, EnumType const EnumValue = EnumType::__last__ >
  struct deserializer {
      static EnumType deserialize(::std::string const& string_in) {
        return deserializer< EnumType, LIBENUM_DEC(EnumType, EnumValue, 1) >::deserialize(string_in);
      }
  };
} // namespace enums

#define LIBENUM_DEFINE_UNKNOWN_SERIALIZER(type_m) \
    template< > \
    struct serializer< type_m, type_m ::__unknown__ > { \
        static ::std::string serialize(type_m const enum_value_in, \
                                       type_m const base_value_in = type_m ::__unknown__, \
                                       ::std::string const& base_string_in = #type_m "::__unknown__") { \
          return serializer< type_m, LIBENUM_NEXT(type_m, __unknown__) >::serialize(enum_value_in, \
                                                                                    type_m ::__unknown__, \
                                                                                    #type_m "::__unknown__"); \
        } \
    };
#define LIBENUM_DEFINE_UNKNOWN_DESERIALIZER(type_m) \
    template< > \
    struct deserializer< type_m, type_m ::__unknown__ > { \
        static type_m deserialize(::std::string const& string_in) { \
          return type_m ::__unknown__; \
        } \
    };

#define LIBENUM_DEFINE_LAST_SERIALIZER(type_m) \
    template< > \
    struct serializer< type_m, type_m ::__last__ > { \
        static ::std::string serialize(type_m const enum_value_in, \
                                       type_m const base_value_in, \
                                       ::std::string const& base_string_in) { \
          return #type_m "::__unknown__ "; \
        } \
    };
#define LIBENUM_DEFINE_LAST_DESERIALIZER(type_m) \
    template< > \
    struct deserializer< type_m, type_m ::__last__ > { \
        static type_m deserialize(::std::string const& string_in) { \
          return deserializer< type_m, LIBENUM_PREV(type_m, __last__) >::deserialize(string_in); \
        } \
    };

#define LIBENUM_DEFINE_DYNAMIC_SERIALIZER(type_m,value_m) \
    template< > \
    struct serializer< type_m, type_m :: value_m > { \
        static ::std::string serialize(type_m const enum_value_in, \
                                       type_m const base_value_in = type_m :: value_m, \
                                       ::std::string const& base_string_in = #type_m "::" #value_m) { \
          if (enum_value_in == type_m :: value_m) { \
            return #type_m "::" #value_m " "; \
          } else { \
            return serializer< type_m, LIBENUM_NEXT(type_m, value_m) >::serialize(enum_value_in, type_m :: value_m, #type_m "::" #value_m); \
          } \
        } \
    };

#define LIBENUM_DEFINE_DYNAMIC_DESERIALIZER(type_m,value_m) \
    template< > \
    struct deserializer< type_m, type_m :: value_m > { \
        static type_m deserialize(::std::string const& string_in) { \
          char const string_value[] = #type_m "::" #value_m; \
          ::std::size_t const string_value_len = sizeof(string_value) - 1; \
          if (string_in.compare(0, string_value_len, string_value) == 0) { \
            if (string_in.length() == string_value_len || string_in[string_value_len] == ' ') { \
              return type_m :: value_m; \
            } else if (string_in[string_value_len] == '+') { \
              return LIBENUM_INC(type_m, \
                                 type_m :: value_m, \
                                 ::boost::lexical_cast< ::std::uint64_t >(string_in.substr(string_value_len + 1, \
                                                                                           string_in.length() - string_value_len - 2) \
                                                                         )\
                                 ); \
            } else { \
              return type_m::__unknown__; \
            } \
          } \
          \
          return deserializer< type_m, LIBENUM_DEC(type_m, type_m :: value_m, 1) >::deserialize(string_in); \
        } \
    }; \

#define LIBENUM_DEFINE_DYNAMIC_SERIALIZER_EACH(r,type_m,value_m) LIBENUM_DEFINE_DYNAMIC_SERIALIZER(type_m,value_m)
#define LIBENUM_DEFINE_DYNAMIC_SERIALIZERS(type_m,values_m) \
  LIBENUM_DEFINE_LAST_SERIALIZER(type_m) \
  BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_DYNAMIC_SERIALIZER_EACH, type_m, values_m) \
  LIBENUM_DEFINE_UNKNOWN_SERIALIZER(type_m)

#define LIBENUM_DEFINE_DYNAMIC_DESERIALIZER_EACH(r,type_m,value_m) LIBENUM_DEFINE_DYNAMIC_DESERIALIZER(type_m,value_m)
#define LIBENUM_DEFINE_DYNAMIC_DESERIALIZERS(type_m,values_m) \
  LIBENUM_DEFINE_UNKNOWN_DESERIALIZER(type_m) \
  BOOST_PP_SEQ_FOR_EACH(LIBENUM_DEFINE_DYNAMIC_DESERIALIZER_EACH, type_m, values_m) \
  LIBENUM_DEFINE_LAST_DESERIALIZER(type_m)

#define LIBENUM_DYNAMIC_ENUM(type_m,values_m) \
    LIBENUM_DECLARE_ENUM(type_m, BOOST_PP_SEQ_ENUM(values_m))
//    namespace enums {
//      LIBENUM_DEFINE_DYNAMIC_SERIALIZERS(type_m##_t,BOOST_PP_SEQ_REVERSE(values_m))
//      LIBENUM_DEFINE_DYNAMIC_DESERIALIZERS(type_m##_t,values_m)
//    }

#endif /* ENUMS_HPP_ */
