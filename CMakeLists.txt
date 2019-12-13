cmake_minimum_required(VERSION 3.14)
project(clerr VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(NO_OUTPUT_DIRS)
endif()

find_package(OpenCL REQUIRED)
find_package(Threads REQUIRED)

add_library(clerr INTERFACE)
add_library(clerr::clerr ALIAS clerr)
target_include_directories(clerr INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(clerr INTERFACE cxx_std_11)
target_link_libraries(clerr INTERFACE OpenCL::OpenCL Threads::Threads ${CMAKE_DL_LIBS})

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(TARGETS clerr EXPORT clerr-targets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/clerr-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    ARCH_INDEPENDENT
)

export(EXPORT clerr-targets
    FILE "${PROJECT_BINARY_DIR}/clerr-targets.cmake"
    NAMESPACE clerr::
)
configure_file(cmake/clerr-config.cmake
    "${PROJECT_BINARY_DIR}/clerr-config.cmake"
    COPYONLY
)

set(config_location ${CMAKE_INSTALL_LIBDIR}/cmake/clerr)
install(EXPORT clerr-targets
    FILE clerr-targets.cmake
    NAMESPACE clerr::
    DESTINATION ${config_location}
)
install(
  FILES "cmake/clerr-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/clerr-config-version.cmake"
  DESTINATION ${config_location}
)

set(BUILD_TESTING OFF CACHE BOOL "")
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test_package)
endif()
