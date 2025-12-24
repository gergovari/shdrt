include(CTest)
include(FetchContent)

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS "*.c")
add_executable(tests ${test_sources})

FetchContent_Declare(
	unity
	GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
	GIT_TAG        v2.6.1
)
FetchContent_MakeAvailable(unity)
target_link_libraries(tests PRIVATE unity)

foreach(test_source ${test_sources})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} PRIVATE unity stc)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
