/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_DYNAMIC_ENUM_HPP_
#define TENUM_DYNAMIC_ENUM_HPP_

#include <boost/lexical_cast.hpp>
#include <tenum/static_enum.hpp>

#define TENUM_SERIALIZE_DYNAMIC_SIGNATURE(type_m,tuples_m) \
  template< > \
  template< > \
  inline ::std::string \
  enum_helper< TENUM_TYPE(type_m) >::serialize_impl< true, false >(TENUM_TYPE(type_m) const value_in, \
                                                                   ::boost::true_type const&, \
                                                                   ::boost::false_type const&)

#define TENUM_SERIALIZE_DYNAMIC_DECLARATION(type_m,tuples_m) \
  TENUM_SERIALIZE_DYNAMIC_SIGNATURE(type_m,tuples_m);

#define TENUM_SERIALIZE_DYNAMIC_DEFINITION(type_m,tuples_m) \
  TENUM_SERIALIZE_DYNAMIC_SIGNATURE(type_m,tuples_m) { \
    TENUM_TYPE(type_m) base_value = get_base_of(value_in); \
    \
    ::std::ostringstream stream; \
    stream << serialize_impl< false, false >(base_value, ::boost::false_type(), ::boost::false_type()); \
    \
    ::boost::uint64_t offset = (TENUM_CAST_UINT(value_in) - TENUM_CAST_UINT(base_value)); \
    if (base_value != TENUM_VALUE_UNKNOWN(type_m) && offset > 0) { \
      stream << TENUM_DEFAULT_SEPARATOR_DYNAMIC_ENUM << offset; \
    } \
    \
    return stream.str(); \
  }

#define TENUM_DESERIALIZE_DYNAMIC_SIGNATURE(type_m,tuples_m) \
  template< > \
  template< > \
  inline TENUM_TYPE(type_m) \
  enum_helper< TENUM_TYPE(type_m) >::deserialize_impl< true, false >(::std::string const& value_in, \
                                                                     ::boost::true_type const&, \
                                                                     ::boost::false_type const&)

#define TENUM_DESERIALIZE_DYNAMIC_DECLARATION(type_m,tuples_m) \
  TENUM_DESERIALIZE_DYNAMIC_SIGNATURE(type_m,tuples_m);

#define TENUM_DESERIALIZE_DYNAMIC_DEFINITION(type_m,tuples_m) \
  TENUM_DESERIALIZE_DYNAMIC_SIGNATURE(type_m,tuples_m) { \
    ::std::size_t separator_pos = value_in.find(TENUM_DEFAULT_SEPARATOR_DYNAMIC_ENUM); \
    TENUM_TYPE(type_m) base_value = deserialize_impl< false, false >(value_in.substr(0, separator_pos), \
                                                                     ::boost::false_type(), \
                                                                     ::boost::false_type()); \
    \
    ::boost::uint64_t offset = 0; \
    if (separator_pos != ::std::string::npos) { \
      offset = ::boost::lexical_cast< ::boost::uint64_t >(value_in.substr(separator_pos + 1)); \
    } \
    \
    return TENUM_CAST_ENUM(type_m,base_value + offset); \
  }

#define TENUM_DYNAMIC_ENUM_SERIALIZATION_DECLARATION(type_m,tuples_m) \
  namespace tenum { \
    template< > struct is_dynamic< TENUM_TYPE(type_m) > : ::boost::true_type {}; \
    TENUM_GET_BASE_OF_DECLARATION(type_m,tuples_m) \
    TENUM_SERIALIZE_DECLARATION(type_m,tuples_m) \
    TENUM_DESERIALIZE_DECLARATION(type_m,tuples_m) \
    TENUM_SERIALIZE_DYNAMIC_DECLARATION(type_m,tuples_m) \
    TENUM_DESERIALIZE_DYNAMIC_DECLARATION(type_m,tuples_m) \
  } \
  TENUM_STREAM_OPERATORS_DECLARATION(type_m)

#define TENUM_DYNAMIC_ENUM_SERIALIZATION_DEFINITION(type_m,tuples_m) \
  namespace tenum { \
    TENUM_GET_BASE_OF_DEFINITION(type_m,tuples_m) \
    TENUM_SERIALIZE_DEFINITION(type_m,tuples_m) \
    TENUM_DESERIALIZE_DEFINITION(type_m,tuples_m) \
    TENUM_SERIALIZE_DYNAMIC_DEFINITION(type_m,tuples_m) \
    TENUM_DESERIALIZE_DYNAMIC_DEFINITION(type_m,tuples_m) \
  } \
  TENUM_STREAM_OPERATORS_DEFINITION(type_m)

#define TENUM_DYNAMIC_ENUM_DECLARATION(type_m,tuples_m) \
  TENUM_ENUM_DEFINITION(type_m,BOOST_PP_SEQ_PUSH_BACK(tuples_m,TENUM_TUPLE_VALUED(lte_unknown,~0ul))) \
  TENUM_ENUM_OPERATORS_DECLARATION(type_m) \
  TENUM_DYNAMIC_ENUM_OPERATORS_DECLARATION(type_m) \
  TENUM_DYNAMIC_ENUM_SERIALIZATION_DECLARATION(type_m,tuples_m)

#define TENUM_DYNAMIC_ENUM_DEFINITION(type_m,tuples_m) \
  TENUM_ENUM_OPERATORS_DEFINITION(type_m) \
  TENUM_DYNAMIC_ENUM_OPERATORS_DEFINITION(type_m) \
  TENUM_DYNAMIC_ENUM_SERIALIZATION_DEFINITION(type_m,tuples_m)

#define TENUM_DYNAMIC_ENUM_I(type_m,tuples_m) \
  TENUM_DYNAMIC_ENUM_DECLARATION(type_m,tuples_m) \
  TENUM_DYNAMIC_ENUM_DEFINITION(type_m,tuples_m)

#define TENUM_DYNAMIC_ENUM(type_m,tuples_m) \
  TENUM_DYNAMIC_ENUM_I(type_m,tuples_m)
#define TENUM_SIMPLE_DYNAMIC_ENUM(type_m,values_m) \
  TENUM_DYNAMIC_ENUM_I(type_m,TENUM_ENUM_VALUES_COMPLETE(values_m))

#endif /* TENUM_DYNAMIC_ENUM_HPP_ */
