cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("ABBA"
    DESCRIPTION "An efficient symbolic representation compression technique for time series"
    VERSION 1.0)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/*.cpp)

add_library(abba STATIC ${SRC_FILES})
target_include_directories(abba PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR})

add_executable(ABBA ${CMAKE_CURRENT_SOURCE_DIR}/runtest.cpp)
target_link_libraries(ABBA PUBLIC abba)