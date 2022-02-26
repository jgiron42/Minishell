# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ereali <ereali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 05:33:00 by ereali            #+#    #+#              #
#    Updated: 2022/02/26 09:48:57 by ereali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parsing

INC_DIR = 	$(shell find includes -type d)

# LIB_DIR		=	srcs/libft

##List every folder where he will find source file
SRC_DIR = 	$(shell find srcs -type d)

##Folder where he will store the .o
OBJ_DIR	= obj

##Add to the vpath the folder find in SRC_DIR
vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

##Add to the vpath the folder find in SRC_DIR
vpath %.h $(foreach dir, $(INC_DIR), $(dir):)

##List every .c found inside SRC_DIR
SRC = tokeniser.c parsing.c utils_lst.c parse_grouping.c parse_list.c \
		parse_pipe.c parse_simple.c print.c expansion.c \
		env.c

##List every .h found inside INC_DIR
INC = parsing.h minishell.h

## Local lib found inside LIB_DIR
LIBS		=	ft

##Transform and place every .o from SRC
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

##Basics	 flags
CFLAGS =	-Wall -Wextra -Werror -g3

##Create the flags to includes every .h needed by this program
IFLAGS =	$(foreach dir, $(INC_DIR), -I $(dir))

# DFLAGS		=	-L $(LIB_DIR)

##Create the flags to includes every .h needed by LIBS
LDLIBS		=	$(foreach lib, $(LIBS), -l$(lib))
##Define the compiler to use
CC =	clang

all: $(NAME)

$(NAME): $(OBJ)
				@echo "Compiling $(NAME) ...\c"
				$(CC) $(OBJ) $(CFLAGS) $(IFLAGS) -L srcs/libft $(LDLIBS) -o $(NAME)
				@echo " DONE"

$(OBJ_DIR)/%.o : %.c
				@mkdir -p $(OBJ_DIR)
				@echo "Compiling $< ...\c"
				@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
				@echo " DONE"

clean:
				@rm -rf $(OBJ_DIR)
				@echo "clean"

fclean:			clean
				@rm -f $(NAME)
				@echo "fclean"

re:				fclean all

.PHONY: all clean fclean re
