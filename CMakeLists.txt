cmake_minimum_required(VERSION 3.30)
include(FetchContent)

project(shdrt LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

file(GLOB_RECURSE shdrt_sources CONFIGURE_DEPENDS src/*.c)
add_library(shdrt SHARED ${shdrt_sources})

FetchContent_Declare(
    stc
    GIT_REPOSITORY https://github.com/stclib/STC.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(stc)
file(GLOB STC_SOURCES "${stc_SOURCE_DIR}/src/*.c")  
add_library(stc STATIC ${STC_SOURCES})
target_include_directories(stc PUBLIC ${stc_SOURCE_DIR}/include)
target_link_libraries(shdrt PRIVATE stc)

option(BUILD_TESTS "Build the test suite" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
