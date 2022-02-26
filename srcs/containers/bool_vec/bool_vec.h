//
// Created by joachim on 2/7/22.
//

#ifndef MINISHELL_V2_BOOL_VEC_H
#define MINISHELL_V2_BOOL_VEC_H

#include <stdlib.h>

typedef bool type_bool_vec;

typedef struct s_bool_vec {
	type_bool_vec	*data;
	int		size;
	int		capacity;
}				t_bool_vec;

int			bool_vec_push(t_bool_vec *v, type_bool_vec value);
type_bool_vec		bool_vec_pop(t_bool_vec *v);
int			bool_vec_reserve(t_bool_vec *v, int new_cap);
int			bool_vec_insert_one(t_bool_vec *v, int pos, type_bool_vec value);
int			bool_vec_resize(t_bool_vec *v, int new_size, type_bool_vec value);
//int		bool_vec_insert_array(t_bool_vec *v, int pos, type *array, int n);
type_bool_vec		bool_vec_erase_one(t_bool_vec *v, int pos);
//void		bool_vec_erase_range(t_bool_vec *v, int pos, int n);
int			bool_vec_cpy(t_bool_vec src, t_bool_vec *dst);
t_bool_vec		bool_vec_init();

#endif
