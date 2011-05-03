/**
 * @file
 * @date May 3, 2011
 */

#ifndef TENUM_DETAIL_HELPER_HPP_
#define TENUM_DETAIL_HELPER_HPP_

#ifndef IN_TENUM_HPP_
#  error "This header should not be included directly. Please use tenum.hpp."
#endif

#include <boost/type_traits/integral_constant.hpp>
#include <boost/static_assert.hpp>

namespace tenum {

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

} // namespace tenum

#endif /* TENUM_DETAIL_HELPER_HPP_ */
