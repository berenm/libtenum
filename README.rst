libtenum : a metaprogramming library to make enums a little bit nicer
======================================================================
.. image:: https://secure.travis-ci.org/berenm/libtenum.png?branch=master
    :alt: Build Status
    :target: https://travis-ci.org/berenm/libtenum

- https://www.ohloh.net/p/libtenum
- http://berenm.github.com/libtenum

WHAT'S INSIDE?
--------------

* Enums now come in three different flavors: static, dynamic and bit fields!
* Enum values are now scoped out of namespace scope. Times of enum values conflict are gone. 
* Nice and customizable (de)serialization for enum to string equivalents. Including dynamic enum values with offset and bit fields arbitrary composition!
* Fresh and light as a native enum, no overhead over enum constants. Limited overhead for serialization support.
* Integer operations as easy and simple as ever.  

CONCEPTS
---------

This library introduces three new variation over the enum concept. The main difference between them is the way these enums are (de)serialized and the available enum / enum and enum / integer operators when this is meaningful (only when using C++0x).

* **Static enums** only allow explicitely defined constants (with specified or implicit integer values), any other value will result in a (de)serialization to special value "unknown".
* **Dynamic enums** allow explicitely defined constants and offsets from these constants, within a given global range (from the first constant to the specified upper integer limit).
 Every value whithin the range will be serializable, any other will result in "unknown". An integer value between two enum constants will be (de)serialized as the nearest lower enum constant plus an offset.
  
 For example, if the enum is defined as { value1 = 1, value2 = 5..., unknown = 10 }, the available range would be from 1 to 9, and the integer 4 will be serialized as "value1#3" which means (value1 + 3).
 
* **Bit fields** only allow combination of explicitely defined constants.
 These will be (de)serialized as a combination of every defined enum constants, any other value will be (de)serialized as "unknown". This flavor restricts constants values to bitwise distinct integers, and to values different from 0 in order to be able to decompose the enum into the specified enum constants. 0 being the special "unknown" value for this flavor.
  
 For example, for an enum defined as { bit1 = 0b001, bit2 = 0b010, bit3 = 0b100... }, an instance of this enum with an integer value of 3 will be serialized as "bit1+bit2", and "bit1+bit3" will be deserialized as an enum instance of integer value 5.

COPYING INFORMATION
--------------------

 Distributed under the Boost Software License, Version 1.0.

 See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt