/**
 * @file
 * @date Apr 20, 2011
 * @todo comment
 */

#ifndef ENUMS2_HPP_
#define ENUMS2_HPP_

#include <boost/preprocessor.hpp>

#define DECLARE_ENUM_EACH(z, data_m, element_m) element_m,
#define DECLARE_ENUM(type_m,values_m) BOOST_PP_SEQ_FOR_EACH(DECLARE_ENUM_EACH,type_m,values_m)

#define E(enum_value_m)            (enum_value_m,,#enum_value_m)
#define V(enum_m,value_m)          (enum_value_m,value_m,#enum_value_m)
#define s(enum_m,string_m)         (enum_value_m,,string_m)
#define F(enum_m,value_m,string_m) (enum_value_m,value_m,string_m)

DECLARE_ENUM(enum_type,
    ((enum_value1,2))
    ((enum_value2,2))
    ((enum_value3,2))
    ((enum_value4,2))
    ((enum_value5,2))
)

DECLARE_ENUM(enum_type,
    (((enum_value1, 2), "bla"))
    ((enum_value2, 4))
    (((enum_value3),"blou"))
    (enum_value4)
    (enum_value5)
)

DECLARE_ENUM(enum_type,
             ((enum_value1)(2)("bla"))
             ((enum_value2)(4))
    (((enum_value3),"blou"))
    (enum_value4)
    (enum_value5)
)

#endif /* ENUMS2_HPP_ */
