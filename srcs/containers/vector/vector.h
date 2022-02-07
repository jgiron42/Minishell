//
// Created by joachim on 2/7/22.
//

#ifndef MINISHELL_V2_DEF_H
#define MINISHELL_V2_DEF_H

#include <stdlib.h>

typedef TYPE type;

typedef struct s_NAME {
	type	*data;
	int		size;
	int		capacity;
}				t_NAME;

int			NAME_push(t_NAME *v, type value);
type		NAME_pop(t_NAME *v);
int			NAME_reserve(t_NAME *v, int new_cap);
int			NAME_insert_one(t_NAME *v, int pos, type value);
//int		NAME_insert_array(t_NAME *v, int pos, type *array, int n);
type		NAME_erase_one(t_NAME *v, int pos);
//void		NAME_erase_range(t_NAME *v, int pos, int n);
int			NAME_cpy(t_NAME src, t_NAME *dst);
t_NAME		NAME_init();

#endif
