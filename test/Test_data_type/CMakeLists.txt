project (Test_data_type)

add_executable("_${PROJECT_NAME}" "${PROJECT_NAME}.cpp")
target_link_libraries("_${PROJECT_NAME}" ordered_tec)

add_test(NAME t_data_type COMMAND "_${PROJECT_NAME}")
