/**
 * @file
 * @date Apr 20, 2011
 * @todo comment
 */

#define BOOST_TEST_MODULE libenum_test
#include <boost/test/unit_test.hpp>
#include "enums.hpp"

template< typename EnumType >
struct is_dynamic: ::boost::false_type {
};

template< typename EnumType >
struct is_bit_flag: ::boost::false_type {
};

LIBENUM_DYNAMIC_ENUM(enum_type,(value1)(value2)(value3=5))

enum_type get_base_of(enum_type const value_in) {
  switch (value_in) {
    case enum_type::value1:
      return enum_type::value1;
    case enum_type::value2:
      return enum_type::value2;
    case enum_type::value3:
      return enum_type::value3;
    case enum_type::__unknown__:
    case enum_type::__last__:
      return enum_type::__unknown__;
    default:
      return get_base_of(LIBENUM_DEC(enum_type,value_in,1));
  }
}

template< typename IsDynamic, typename IsBitFlag >
::std::string serialize(enum_type& enum_value_in);

::std::string serialize(enum_type const value_in, ::boost::false_type const&) {
  switch (value_in) {
    case enum_type::value1:
      return "value1";
    case enum_type::value2:
      return "value2";
    case enum_type::value3:
      return "value3";
    case enum_type::__unknown__:
    case enum_type::__last__:
    default:
      return "__unknown__";
  }
}

enum_type deserialize(::std::string const& value_in, ::boost::false_type const&) {
  if (value_in == "value1") {
    return enum_type::value1;
  } else if (value_in == "value2") {
    return enum_type::value2;
  } else if (value_in == "value3") {
    return enum_type::value3;
  } else {
    return enum_type::__unknown__;
  }
}

::std::string serialize(enum_type const value_in, ::boost::true_type const&) {
  enum_type base_value = get_base_of(value_in);

  ::std::ostringstream stream;
  stream << serialize(base_value, ::boost::false_type());

  ::std::uint64_t offset = (LIBENUM_UINT(value_in) - LIBENUM_UINT(base_value));
  if (base_value != enum_type::__unknown__ && offset > 0) {
    stream << "#" << offset;
  }

  return stream.str();
}

enum_type deserialize(::std::string const& value_in, ::boost::true_type const&) {
  ::std::size_t separator_pos = value_in.find('#');
  enum_type base_value = deserialize(value_in.substr(0, separator_pos), ::boost::false_type());

  ::std::uint64_t offset = 0;
  if (separator_pos != ::std::string::npos) {
    offset = ::boost::lexical_cast< ::std::uint64_t >(value_in.substr(separator_pos + 1));
  }

  return LIBENUM_INC(enum_type,base_value,offset);
}

::std::string serialize_bitflag(enum_type const value_in) {
  enum_type base_value = get_base_of(value_in);

  ::std::ostringstream stream;
  stream << serialize(base_value, ::boost::false_type());

  ::std::uint64_t offset = (LIBENUM_UINT(value_in) - LIBENUM_UINT(base_value));
  if (base_value != enum_type::__unknown__ && offset > 0) {
    stream << "#" << offset;
  }

  return stream.str();
}

enum_type deserialize_bitflag(::std::string const& value_in) {
  ::std::size_t separator_pos = value_in.find('#');
  enum_type base_value = deserialize(value_in.substr(0, separator_pos), ::boost::false_type());

  ::std::uint64_t offset = 0;
  if (separator_pos != ::std::string::npos) {
    offset = ::boost::lexical_cast< ::std::uint64_t >(value_in.substr(separator_pos + 1));
  }

  return LIBENUM_INC(enum_type,base_value,offset);
}

::std::string serialize(enum_type const value_in) {
  return serialize(value_in, is_dynamic< enum_type > ());
}

enum_type deserialize(::std::string const& value_in) {
  return deserialize(value_in, is_dynamic< enum_type > ());
}

template< typename OutputStream >
OutputStream& operator<<(OutputStream& ostream, enum_type const enum_in) {
  ostream << serialize(enum_in);
  return ostream;
}

BOOST_AUTO_TEST_CASE( test1 )
{
  enum_type_t enum_value = LIBENUM_NEXT(enum_type,value2);
  ::std::ostringstream stream;
  stream << enum_value;
  ::std::string value_string = stream.str();
  ::std::cout << value_string << ::std::endl;

  enum_value = deserialize(value_string);
  ::std::cout << enum_value << ::std::endl;
}
