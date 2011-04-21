/**
 * @file
 * @date Apr 20, 2011
 * @todo comment
 */

#define BOOST_TEST_MODULE libenum_test
#include <boost/test/unit_test.hpp>

#define LIBENUM_USE_SHORTCUTS 1
#include "enums.hpp"

_dynamic_enum(enum_type,
    _v(value1,=2)
    _vn(value2,=5,"test_value2")
    _(value3)
)

_enum_s(enum_type2,
    (value1)(value2)(value3)
)

BOOST_AUTO_TEST_CASE( test2 )
{
  enum_type_t enum_value = LIBENUM_DEC(enum_type, enum_type::value2, 1);
  ::std::stringstream stream;
  stream << enum_value;
  ::std::string value_string = stream.str();
  ::std::cout << value_string << ::std::endl;

  stream >> enum_value;
  ::std::cout << enum_value << ::std::endl;
}
