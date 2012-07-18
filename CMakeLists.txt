cmake_minimum_required(VERSION 2.8)
find_package(Git REQUIRED)
message(STATUS "updating libtenum submodules...")
execute_process(COMMAND git submodule update --init WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_QUIET)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(GNUInstallDirs)

project(libtenum CXX)

find_package(Boost COMPONENTS unit_test_framework test_exec_monitor REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# -------------------------------------------------------------------------
# project version
set(LIBTENUM_VERSION 0.9.3)

include_directories(include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# -------------------------------------------------------------------------
# installation
install(DIRECTORY include/tenum
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# -------------------------------------------------------------------------
# tests
enable_testing()

add_executable(unit-test-bit-field
  test/test_bit_field.cpp
)
target_link_libraries(unit-test-bit-field ${Boost_LIBRARIES})
add_test(unit-test-bit-field unit-test-bit-field)

add_executable(unit-test-dynamic-enum
  test/test_dynamic_enum.cpp
)
target_link_libraries(unit-test-dynamic-enum ${Boost_LIBRARIES})
add_test(unit-test-dynamic-enum unit-test-dynamic-enum)

add_executable(unit-test-static-enum
  test/test_static_enum.cpp
)
target_link_libraries(unit-test-static-enum ${Boost_LIBRARIES})
add_test(unit-test-static-enum unit-test-static-enum)
