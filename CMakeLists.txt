cmake_minimum_required(VERSION 3.10)
project(ipc-practice C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall)

add_subdirectory(pipe)
add_subdirectory(fifo)
add_subdirectory(dup2_pipe)
add_subdirectory(socket)
add_subdirectory(shm)
add_subdirectory(sem_shm)
add_subdirectory(signals)
