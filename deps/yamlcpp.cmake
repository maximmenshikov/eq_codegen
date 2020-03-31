# jsmn build rules
# A minimal JSON parsing library
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(FetchContent)

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")

FetchContent_Declare(
  yaml-cpp-stub
  GIT_REPOSITORY "https://github.com/maximmenshikov/yaml-cpp.git"
  CMAKE_ARGS -DYAML_CPP_BUILD_TESTS=OFF
)

add_compile_options(-fPIC)
FetchContent_MakeAvailable(yaml-cpp-stub)
