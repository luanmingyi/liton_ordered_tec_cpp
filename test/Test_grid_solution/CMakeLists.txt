project (Test_grid_solution)

add_executable("_${PROJECT_NAME}" "${PROJECT_NAME}.cpp")
target_link_libraries("_${PROJECT_NAME}" ordered_tec)

add_test(NAME t_grid_solution COMMAND "_${PROJECT_NAME}")
