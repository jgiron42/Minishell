cmake_minimum_required(VERSION 3.20)
project(minishell_v2 C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

add_executable(minishell_v2
        includes/minishell.h
        srcs/env/env.c
        srcs/env/serialize_env.c
        srcs/env/dupenv.c
        srcs/env/init_env.c
        srcs/env/parse_env.c
        srcs/execution/exec.c
        srcs/utils/path_utils.c
        )
