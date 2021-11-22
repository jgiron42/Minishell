cmake_minimum_required(VERSION 3.20)
project(minishell_v2 C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

add_executable(minishell_v2
        includes/minishell.h
        srcs/env.c
        srcs/serialize_env.c)
