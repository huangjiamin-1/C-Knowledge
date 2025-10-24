cmake_minimum_required(VERSION 3.10.0)
project(C++Constrcutors VERSION 1.0.0 DESCRIPTION "C++ Constructors Base")
set(CMAKE_CXX_STANDARD 14)
file(GLOB_RECURSE EXE_NAME "main_*.cpp")
# 定义函数，从文件中提取出数字main_*.cpp
function(extract_number filename output_var)
    string(REGEX MATCH "main_([0-9]+)\\.cpp" _ ${filename})
    # message(STATUS ${CMAKE_MATCH_1})
    set(${output_var} ${CMAKE_MATCH_1} PARENT_SCOPE)
endfunction()

# 为每个文件关联其数字，并按数字排序
set(sort_files "")
foreach(file ${EXE_NAME})
    extract_number(${file} num)
    # 用 "数字|文件名" 的形式暂存，便于排序
    list(APPEND sort_files "${num}|${file}")
endforeach()

# 按数字大小排序（使用 cmake 的 SORT 命令，默认按字符串数字排序）
list(SORT sorted_files)

# 提取排序后的文件名 
set(EXE_NAME "")
foreach(item ${sort_files})
    # 使用;来将字符串分割为两个字符串，当做list LEN=2
    string(REPLACE "|" ";" parts ${item})
    list(GET parts 1 file)
    list(APPEND EXE_NAME ${file})
endforeach()

# 生成可执行文件（此时 EXE_NAME 已按数字顺序排列）
list(LENGTH EXE_NAME EXE_LENGTH)
message(STATUS "可执行文件的数量: ${EXE_LENGTH}")
math(EXPR EXE_LENGTH "${EXE_LENGTH} - 1")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

foreach(item RANGE 0 ${EXE_LENGTH})
    list(GET EXE_NAME ${item} FILE_NAME)
    extract_number(${FILE_NAME} num)
    add_executable(Constructor_${num} ${FILE_NAME})
endforeach()