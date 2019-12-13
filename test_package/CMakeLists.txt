cmake_minimum_required(VERSION 3.14)
project(clerr-test LANGUAGES CXX)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(NO_OUTPUT_DIRS)
endif()

set(TARGET_OPENCL_VERSION 220 CACHE STRING "OpenCL Version to test")

find_package(Boost REQUIRED)
find_package(doctest REQUIRED)

if(NOT TARGET clerr::clerr)
    find_package(clerr REQUIRED)
endif()

add_executable(cxx11 cxx11.cpp main.cpp)
target_link_libraries(cxx11 PRIVATE doctest::doctest clerr::clerr)
target_compile_definitions(cxx11 PRIVATE CL_TARGET_OPENCL_VERSION=${TARGET_OPENCL_VERSION})
target_compile_features(cxx11 PRIVATE cxx_std_11)

add_executable(cxx17 cxx17.cpp main.cpp)
target_link_libraries(cxx17 PRIVATE doctest::doctest clerr::clerr)
target_include_directories(cxx17 PRIVATE ${Boost_INCLUDE_DIR})
target_compile_definitions(cxx17 PRIVATE CL_TARGET_OPENCL_VERSION=${TARGET_OPENCL_VERSION})
target_compile_features(cxx17 PRIVATE cxx_std_17)

add_test(NAME cxx11_tests COMMAND cxx11)
add_test(NAME cxx17_tests COMMAND cxx17)
