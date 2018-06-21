project (Test_two_zone)

add_executable("_${PROJECT_NAME}" "${PROJECT_NAME}.cpp")
target_link_libraries("_${PROJECT_NAME}" ordered_tec)

add_test(NAME t_two_zone COMMAND "_${PROJECT_NAME}")
