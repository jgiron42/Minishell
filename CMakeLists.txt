cmake_minimum_required(VERSION 3.20)
project(minishell_v2 C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -Wall -Werror -Wextra")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -Wall -Werror -Wextra")

add_library(LIBFT
        srcs/libft/ft_atoi.c
        srcs/libft/ft_bzero.c
        srcs/libft/ft_calloc.c
        srcs/libft/ft_isalnum.c
        srcs/libft/ft_isalpha.c
        srcs/libft/ft_isascii.c
        srcs/libft/ft_isdigit.c
        srcs/libft/ft_isprint.c
        srcs/libft/ft_itoa.c
        srcs/libft/ft_memccpy.c
        srcs/libft/ft_memchr.c
        srcs/libft/ft_memcmp.c
        srcs/libft/ft_memcpy.c
        srcs/libft/ft_memset.c
        srcs/libft/ft_putchar_fd.c
        srcs/libft/ft_putendl_fd.c
        srcs/libft/ft_putnbr_fd.c
        srcs/libft/ft_putstr_fd.c
        srcs/libft/ft_split.c
        srcs/libft/ft_strchr.c
        srcs/libft/ft_strcmp.c
        srcs/libft/ft_strcpy.c
        srcs/libft/ft_strdup.c
        srcs/libft/ft_strjoin.c
        srcs/libft/ft_strlcat.c
        srcs/libft/ft_strlcpy.c
        srcs/libft/ft_strlen.c
        srcs/libft/ft_strmapi.c
        srcs/libft/ft_strncmp.c
        srcs/libft/ft_strnstr.c
        srcs/libft/ft_strrchr.c
        srcs/libft/ft_strtrim.c
        srcs/libft/ft_substr.c
        srcs/libft/ft_tolower.c
        srcs/libft/ft_toupper.c)

file(GLOB SOURCES srcs/*/*.c srcs/containers/*_vec/*.c  includes/*.h srcs/main.c)

add_executable(minishell_v2 ${SOURCES})

target_link_libraries(minishell_v2 LIBFT readline)
