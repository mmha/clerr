include(CMakeFindDependencyMacro)
find_dependency(OpenCL REQUIRED)
find_dependency(Threads REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/clerr-targets.cmake")
