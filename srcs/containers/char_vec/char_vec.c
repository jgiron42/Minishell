
#include "char_vec.h"

t_char_vec	char_vec_init()
{
	return ((t_char_vec){});
}

int			char_vec_reserve(t_char_vec *v, int new_cap)
{
	type_char_vec	*tmp;

	if (new_cap < v->capacity)
		return (1);
	tmp = malloc(sizeof(type_char_vec) * new_cap);
	if (!tmp)
		return (0);
	v->data = tmp;
	v->capacity = new_cap;
	return (1);
}

int			char_vec_push(t_char_vec *v, type_char_vec value)
{
	if (v->size <= v->capacity)
	{
		if (v->capacity == 0 && char_vec_reserve(v, 1) == 0)
			return (0);
		else if (char_vec_reserve(v, v->capacity * 2) == 0)
			return (0);
	}
	v->data[v->size] = value;
	v->size++;
	return (1);
}

type_char_vec		char_vec_pop(t_char_vec *v)
{
	if (v->size)
	{
		v->size--;
		return (v->data[v->size]);
	}
	return (0);
}

int		char_vec_cpy(t_char_vec src, t_char_vec *dst)
{
	int	i;

	if (src.size == 0)
	{
		*dst = char_vec_init();
		return (1);
	}
	if (char_vec_reserve(dst, src.size) == 0)
		return (0);
	i = 0;
	while (i < src.size)
	{
		dst->data[i] = src.data[i];
		i++;
	}
	dst->size = src.size;
	return (1);
}

int			char_vec_insert_one(t_char_vec *v, int pos, type_char_vec value)
{
	int	i;
	if (v->size == v->capacity)
	{
		if (v->capacity == 0 && char_vec_reserve(v, 1) == 0)
			return (0);
		else if (char_vec_reserve(v, v->capacity * 2) == 0)
			return (0);
	}
	i = v->size;
	while (i > pos)
	{
		v->data[i] = v->data[i - 1];
		--i;
	}
	v->data[i] = value;
	v->size++;
	return (1);
}

int			char_vec_resize(t_char_vec *v, int new_size, type_char_vec value)
{
	if (new_size < 0)
		return(1);
	else if (new_size <= v->size)
		v->size = new_size;
	else
	{
		if (new_size > v->capacity) {
			if (new_size < v->capacity * 2 && !char_vec_reserve(v, v->capacity * 2))
				return (0);
			else if (new_size > v->capacity * 2 && !char_vec_reserve(v, new_size))
				return (0);
		}
		while (--new_size >= v->size)
			v->data[new_size] = value;
		v->size = new_size;
	}
	return (1);
}

type_char_vec			char_vec_erase_one(t_char_vec *v, int pos)
{
	type_char_vec ret;

	ret = v->data[pos];
	--v->size;
	while (pos < v->size)
	{
		v->data[pos] = v->data[pos + 1];
		pos++;
	}
	return (ret);
}
