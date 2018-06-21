project (Test_using_time)

add_executable("_${PROJECT_NAME}" "${PROJECT_NAME}.cpp")
target_link_libraries("_${PROJECT_NAME}" ordered_tec)

add_test(NAME t_using_time COMMAND "_${PROJECT_NAME}")
