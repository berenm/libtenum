/**
 * @file
 * @date Apr 20, 2011
 * @todo comment
 */

#define BOOST_TEST_MODULE libenum_test
#include <boost/test/unit_test.hpp>
#include "enums.hpp"

LIBENUM_DYNAMIC_ENUM(enum_type,(value1)(value2)(value3))

template< typename OutputStream >
OutputStream& operator<<(OutputStream& ostream, enum_type const enum_in) {
  ostream << enums::serializer< enum_type >::serialize(enum_in);
  return ostream;
}

BOOST_AUTO_TEST_CASE( test1 )
{
  enum_type_t enum_value = enum_type::value1;
  ::std::cout << enum_value << ::std::endl;
}
