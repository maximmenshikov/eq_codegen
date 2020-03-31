# Code generator build script
# @author Maxim Menshikov (info@menshikov.org)
cmake_minimum_required(VERSION 3.0)

project(codegen)

option(CODEGEN_ENABLE_DEPRECATED "Enable deprecated models"         OFF)
option(CODEGEN_ENABLE_CLANG_TIDY "Enable codegen clang-tidy"        OFF)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/yamlcpp.cmake")
    include(${CMAKE_CURRENT_SOURCE_DIR}/deps/yamlcpp.cmake)
endif()

set(SRC src/main.cpp
        model/EnumVerify.cpp
        model/Command.cpp
        model/VMIRMapping.cpp
        src/ClassData.cpp
        src/CodegenParam.cpp
        src/ConstructorData.cpp
        src/DataFetcher.cpp
        src/MemberData.cpp
        src/Utils.cpp
    )

if (CODEGEN_ENABLE_DEPRECATED)
     set(SRC ${SRC} deprecated/Enum.cpp
                    deprecated/Expression.cpp
                    deprecated/Header.cpp
                    deprecated/OperationEnum.cpp)
endif ()

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE include model)

if (CODEGEN_ENABLE_DEPRECATED)
     target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_DEPRECATED)
     target_include_directories(${PROJECT_NAME} PRIVATE deprecated)
endif ()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} yaml-cpp stdc++fs)

if (CODEGEN_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_BINARY NAMES "clang-tidy")
    if (CLANG_TIDY_BINARY)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                              CXX_CLANG_TIDY "${CLANG_TIDY_BINARY}")
    else ()
        message(STATUS "clang-tidy not found")
    endif()
endif()
