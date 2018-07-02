project (Test_xml)

add_executable("_${PROJECT_NAME}" "${PROJECT_NAME}.cpp")
target_link_libraries("_${PROJECT_NAME}" ordered_tec tinyxml)

add_test(NAME t_xml COMMAND "_${PROJECT_NAME}")
