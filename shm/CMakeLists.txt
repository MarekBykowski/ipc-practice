add_executable(shm_writer writer.c)
add_executable(shm_reader reader.c)

target_link_libraries(shm_writer rt)
target_link_libraries(shm_reader rt)
