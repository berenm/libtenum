cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CMakeExtraBootstrap)
include(GNUInstallDirs)
include(ParseVersion)
include(AddSubmodule)
include(CheckCXXCompilerFlag)

project(libtenum CXX)
parse_version(libtenum VERSION 0.9.5)

check_cxx_compiler_flag("-std=c++11" TENUM_COMPILER_KNOWS_CXX11)
if(TENUM_COMPILER_KNOWS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  check_cxx_compiler_flag("-std=c++0x" TENUM_COMPILER_KNOWS_CXX0X)
  if(TENUM_COMPILER_KNOWS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  endif()
endif()

find_package(Boost COMPONENTS unit_test_framework test_exec_monitor REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(include)

# -------------------------------------------------------------------------
# installation
install(DIRECTORY include/tenum
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES include/tenum.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# -------------------------------------------------------------------------
# tests
if(BUILD_TESTS)
  enable_testing()

  add_executable(unit-test-tenum-bit-field test/test_bit_field.cpp)
  target_link_libraries(unit-test-tenum-bit-field ${Boost_LIBRARIES})
  add_test(unit-test-tenum-bit-field unit-test-tenum-bit-field)

  add_executable(unit-test-tenum-dynamic-enum test/test_dynamic_enum.cpp)
  target_link_libraries(unit-test-tenum-dynamic-enum ${Boost_LIBRARIES})
  add_test(unit-test-tenum-dynamic-enum unit-test-tenum-dynamic-enum)

  add_executable(unit-test-tenum-static-enum test/test_static_enum.cpp)
  target_link_libraries(unit-test-tenum-static-enum ${Boost_LIBRARIES})
  add_test(unit-test-tenum-static-enum unit-test-tenum-static-enum)
endif()

if(ENABLE_GCOVERALLS)
  include(GCoveralls)
  enable_gcoveralls()
endif()
