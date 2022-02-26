//
// Created by joachim on 2/7/22.
//

#ifndef MINISHELL_V2_CHAR_VEC_H
#define MINISHELL_V2_CHAR_VEC_H

#include <stdlib.h>
#include <stdbool.h>

typedef char type_char_vec;

typedef struct s_char_vec {
	type_char_vec	*data;
	int		size;
	int		capacity;
}				t_char_vec;

int			char_vec_push(t_char_vec *v, type_char_vec value);
type_char_vec		char_vec_pop(t_char_vec *v);
int			char_vec_reserve(t_char_vec *v, int new_cap);
int			char_vec_insert_one(t_char_vec *v, int pos, type_char_vec value);
int			char_vec_resize(t_char_vec *v, int new_size, type_char_vec value);
//int		char_vec_insert_array(t_char_vec *v, int pos, type *array, int n);
type_char_vec		char_vec_erase_one(t_char_vec *v, int pos);
//void		char_vec_erase_range(t_char_vec *v, int pos, int n);
int			char_vec_cpy(t_char_vec src, t_char_vec *dst);
t_char_vec		char_vec_init();

#endif
