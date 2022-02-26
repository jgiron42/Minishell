//
// Created by joachim on 2/7/22.
//

#ifndef MINISHELL_V2_STR_VEC_H
#define MINISHELL_V2_STR_VEC_H

#include <stdlib.h>

typedef char* type_str_vec;

typedef struct s_str_vec {
	type_str_vec	*data;
	int		size;
	int		capacity;
}				t_str_vec;

int			str_vec_push(t_str_vec *v, type_str_vec value);
type_str_vec		str_vec_pop(t_str_vec *v);
int			str_vec_reserve(t_str_vec *v, int new_cap);
int			str_vec_insert_one(t_str_vec *v, int pos, type_str_vec value);
int			str_vec_resize(t_str_vec *v, int new_size, type_str_vec value);
//int		str_vec_insert_array(t_str_vec *v, int pos, type *array, int n);
type_str_vec		str_vec_erase_one(t_str_vec *v, int pos);
//void		str_vec_erase_range(t_str_vec *v, int pos, int n);
int			str_vec_cpy(t_str_vec src, t_str_vec *dst);
t_str_vec		str_vec_init();

#endif
