//
// Created by joachim on 2/7/22.
//

#ifndef STR_VEC_H
# define STR_VEC_H

# include <stdlib.h>
# include <stdbool.h>

typedef char*	t_type_str_vec;

typedef struct s_str_vec {
	type_str_vec	*data;
	int				size;
	int				capacity;
}				t_str_vec;

int				str_vec_push(t_str_vec *v, t_type_str_vec value);
t_type_str_vec	str_vec_pop(t_str_vec *v);
int				str_vec_concat(t_str_vec *v, t_str_vec other);
int				str_vec_reserve(t_str_vec *v, int new_cap);
int				str_vec_insert_one(t_str_vec *v, int pos, t_type_str_vec value);
int				str_vec_resize(t_str_vec *v, int new_size,
					t_type_str_vec value);
t_type_str_vec	str_vec_erase_one(t_str_vec *v, int pos);
int				str_vec_cpy(t_str_vec src, t_str_vec *dst);
t_str_vec		str_vec_init(void);

#endif
