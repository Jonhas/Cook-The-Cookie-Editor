cmake_minimum_required(VERSION 3.0)
project(Cook)
set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SRC   src/*.c 
                        include/*.h)

add_executable(cook ${SRC})
target_compile_options(cook PUBLIC -g -std=c11 -Wall -Wextra)

set(CPACK_PACKAGE_NAME "Cook")
set(CPACK_PACKAGE_VERSION "0.0.1")
