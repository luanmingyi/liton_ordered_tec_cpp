project (Test_zone_size)

add_executable("_${PROJECT_NAME}" "${PROJECT_NAME}.cpp")
target_link_libraries("_${PROJECT_NAME}" ordered_tec)

add_test(NAME t_zone_size COMMAND "_${PROJECT_NAME}")
