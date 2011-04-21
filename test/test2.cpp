/**
 * @file
 * @date Apr 20, 2011
 * @todo comment
 */
#define BOOST_TEST_MODULE libenum_test
#include <boost/test/unit_test.hpp>
#include "enums2.hpp"
#define element_m ((value1)(=2))
#define element2_m BOOST_PP_IF( BOOST_PP_IS_UNARY(element_m), \
    element_m, \
    ((element_m)())(BOOST_PP_STRINGIZE(element_m)) \
) \

#define element3_m BOOST_PP_IF( BOOST_PP_IS_UNARY(LIBENUM_TUPLE_FIRST(element2_m)), \
                            element2_m, \
                            ((LIBENUM_TUPLE_FIRST(element2_m))(LIBENUM_TUPLE_SECOND(element2_m)))(BOOST_PP_STRINGIZE(LIBENUM_TUPLE_FIRST(element2_m))) \
               )
#define element4_m BOOST_PP_IF( BOOST_PP_EQUAL(2, BOOST_PP_SEQ_SIZE(LIBENUM_TUPLE_FIRST(element3_m))), \
                                         element3_m, \
                                         ((LIBENUM_TUPLE_ELEM(element3_m))())(LIBENUM_TUPLE_NAME(element3_m)) \
                            )

element4_m

LIBENUM_COMPLETE_VALUES(((value1)(=2)))
LIBENUM_COMPLETE_VALUES((((value2))("test_value2")))
LIBENUM_COMPLETE_VALUES((value3))

#define complete_sequence LIBENUM_COMPLETE_SEQ(sequence)

LIBENUM_STATIC_ENUM(enum_type,
    complete_sequence
)

BOOST_AUTO_TEST_CASE( test1 )
{
  enum_type_t enum_value = enum_type::value1;
  ::std::stringstream stream;
  stream << enum_value;
  ::std::string value_string = stream.str();
  ::std::cout << value_string << ::std::endl;

  stream >> enum_value;
  ::std::cout << enum_value << ::std::endl;

  //  ::std::cout << enum_helper< enum_type >::serialize(enum_value) << ::std::endl;
  //  ::std::cout
  //      << enum_helper< enum_type >::serialize(enum_helper< enum_type >::deserialize("value1+value2+value3"))
  //      << ::std::endl;
  //
  //  enum_value = enum_helper< enum_type >::deserialize(value_string);
  //  ::std::cout << enum_value << ::std::endl;
}
