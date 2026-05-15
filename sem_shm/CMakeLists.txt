add_executable(proc_a proc_a.c)
add_executable(proc_b proc_b.c)

target_link_libraries(proc_a rt pthread)
target_link_libraries(proc_b rt pthread)
