project (Test_single_zone)

add_executable("_${PROJECT_NAME}" "${PROJECT_NAME}.cpp")
target_link_libraries("_${PROJECT_NAME}" ordered_tec)

add_test(NAME t_single_zone COMMAND "_${PROJECT_NAME}")
