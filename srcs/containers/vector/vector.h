//
// Created by joachim on 2/7/22.
//

#ifndef MINISHELL_V2_DEF_H
#define MINISHELL_V2_DEF_H

#include <stdlib.h>
#include <stdbool.h>

typedef TYPE type_NAME;

typedef struct s_NAME {
	type_NAME	*data;
	int		size;
	int		capacity;
}				t_NAME;

int			NAME_push(t_NAME *v, type_NAME value);
type_NAME		NAME_pop(t_NAME *v);
int			NAME_concat(t_NAME *v, t_NAME other);
int			NAME_reserve(t_NAME *v, int new_cap);
int			NAME_insert_one(t_NAME *v, int pos, type_NAME value);
int			NAME_resize(t_NAME *v, int new_size, type_NAME value);
//int		NAME_insert_array(t_NAME *v, int pos, type *array, int n);
type_NAME		NAME_erase_one(t_NAME *v, int pos);
//void		NAME_erase_range(t_NAME *v, int pos, int n);
int			NAME_cpy(t_NAME src, t_NAME *dst);
t_NAME		NAME_init();

#endif
