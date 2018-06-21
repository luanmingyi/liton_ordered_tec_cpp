project (Test_echo_mode)

add_executable("_${PROJECT_NAME}" "${PROJECT_NAME}.cpp")
target_link_libraries("_${PROJECT_NAME}" ordered_tec)

add_test(NAME t_echo_mode COMMAND "_${PROJECT_NAME}")
