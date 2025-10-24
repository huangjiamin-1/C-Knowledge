cmake_minimum_required(VERSION 3.10.0)
project(C++great_less VERSION 1.0.0 DESCRIPTION "C++ 实现大于等于操作符类")
set(CMAKE_CXX_STANDARD 14)
file(GLOB_RECURSE EXE_NAME "main_*.cpp")
list(LENGTH EXE_NAME EXE_LENGTH)
math(EXPR EXE_LENGTH "${EXE_LENGTH} - 1")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

foreach(item RANGE 0 ${EXE_LENGTH})
    list(GET EXE_NAME ${item} FILE_NAME)
    add_executable(GreatLess_${item} ${FILE_NAME})
endforeach()

