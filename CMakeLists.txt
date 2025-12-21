cmake_minimum_required(VERSION 3.30)

project(shdrt LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")


include(FetchContent)

FetchContent_Declare(
    stc
    GIT_REPOSITORY https://github.com/stclib/STC.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(stc)

add_executable(app)
target_include_directories(app PRIVATE ${stc_SOURCE_DIR}/include)

file(GLOB_RECURSE app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
