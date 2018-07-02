cmake_minimum_required (VERSION 3.5)

project(liton_ordered_tec)

add_library(tinyxml STATIC "../../scr/tinyxml2/tinyxml2.cpp")

add_library(ordered_tec STATIC "../scr/liton_ordered_tec/ordered_tec.cpp")
target_include_directories(ordered_tec PUBLIC "../scr/liton_ordered_tec")
target_compile_definitions(ordered_tec
PUBLIC "$<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>"
PUBLIC OT_TINYXML)
target_link_libraries(ordered_tec tinyxml)

enable_testing()
add_subdirectory(Test_single_zone)
add_subdirectory(Test_two_zone)
add_subdirectory(Test_grid_solution)
add_subdirectory(Test_multi_file)
add_subdirectory(Test_data_type)
add_subdirectory(Test_echo_in_file)
add_subdirectory(Test_echo_mode)
add_subdirectory(Test_log)
add_subdirectory(Test_using_time)
add_subdirectory(Test_zone_size)
add_subdirectory(Test_xml)
add_subdirectory(Test_auxiliary)
