/**
 * @file
 * @date Apr 20, 2011
 * @todo comment
 */

#define BOOST_TEST_MODULE libenum_test
#include <boost/test/unit_test.hpp>
#include "enums2.hpp"

//LIBENUM_STATIC_ENUM(enum_type,
//    ((value1,=2))
//    (((value2),"test_value2"))
//    (value3)
//)

#define LIST ((value1,=2), (((value2),"test_value2"), (value3, BOOST_PP_NIL)))

#define element_0 value2
#define element_1 (value2)
#define element_2 (value2,1)
#define element_3 ((value2),"test_value2")
#define element_4 ((value2,1),"test_value2")

struct test {
    BOOST_PP_IF( BOOST_PP_IS_UNARY(element_1) ,
        BOOST_STATIC_ASSERT(false);,
        BOOST_STATIC_ASSERT(false);
    )
};
//
//BOOST_PP_IF( BOOST_PP_IS_BINARY(element_m),
//    BOOST_PP_IF( BOOST_PP_IS_BINARY( LIBENUM_TUPLE_FIRST(element_m) ),
//        (
//            (
//                LIBENUM_TUPLE_FIRST(LIBENUM_TUPLE_FIRST(element_m)),
//                LIBENUM_TUPLE_SECOND(LIBENUM_TUPLE_FIRST(element_m))
//            ),
//            LIBENUM_TUPLE_SECOND(element_m)
//        ),
//        (
//            (
//                LIBENUM_TUPLE_FIRST(element_m),
//                LIBENUM_TUPLE_SECOND(element_m)
//            ),
//            BOOST_PP_STRINGIZE( LIBENUM_TUPLE_FIRST(element_m) )
//        )
//    ),
//    (
//        (
//            element_m,
//        ),
//        BOOST_PP_STRINGIZE( element_m )
//    )
//)

//BOOST_PP_LIST_TRANSFORM(LIBENUM_COMPLETE_VALUES_TRANSFORM, ~, LIST)

BOOST_AUTO_TEST_CASE( test1 )
{
  //  enum_type_t enum_value = enum_type::value1;
  //  ::std::stringstream stream;
  //  stream << enum_value;
  //  ::std::string value_string = stream.str();
  //  ::std::cout << value_string << ::std::endl;
  //
  //  stream >> enum_value;
  //  ::std::cout << enum_value << ::std::endl;

  //  ::std::cout << enum_helper< enum_type >::serialize(enum_value) << ::std::endl;
  //  ::std::cout
  //      << enum_helper< enum_type >::serialize(enum_helper< enum_type >::deserialize("value1+value2+value3"))
  //      << ::std::endl;
  //
  //  enum_value = enum_helper< enum_type >::deserialize(value_string);
  //  ::std::cout << enum_value << ::std::endl;
}
