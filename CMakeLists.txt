project(prefix_tree)

set(CMAKE_C_STANDARD 11)

add_library(prefix_tree src/tree.c)

add_executable(prefix_tree_example tests/main.c)

target_link_libraries(prefix_tree_example prefix_tree)
