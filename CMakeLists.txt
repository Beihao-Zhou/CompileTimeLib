cmake_minimum_required(VERSION 3.12)
project(CompileTimeLib VERSION 1.0 DESCRIPTION "A compile-time container and algorithm library" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(test_static_vector tests/static_vector.cpp)
target_link_libraries(test_static_vector ${GTEST_BOTH_LIBRARIES} pthread)
add_test(NAME StaticVectorTest COMMAND test_static_vector)

add_executable(test_static_set tests/static_set.cpp)
target_link_libraries(test_static_set ${GTEST_BOTH_LIBRARIES} pthread)
add_test(NAME StaticSetTest COMMAND test_static_set)
