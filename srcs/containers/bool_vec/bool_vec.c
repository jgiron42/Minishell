
#include "bool_vec.h"

t_bool_vec	bool_vec_init()
{
	return ((t_bool_vec){});
}

int			bool_vec_reserve(t_bool_vec *v, int new_cap)
{
	type_bool_vec	*tmp;

	if (new_cap < v->capacity)
		return (1);
	tmp = malloc(sizeof(type_bool_vec) * new_cap);
	if (!tmp)
		return (0);
	v->data = tmp;
	v->capacity = new_cap;
	return (1);
}

int			bool_vec_push(t_bool_vec *v, type_bool_vec value)
{
	if (v->size <= v->capacity)
	{
		if (v->capacity == 0 && bool_vec_reserve(v, 1) == 0)
			return (0);
		else if (bool_vec_reserve(v, v->capacity * 2) == 0)
			return (0);
	}
	v->data[v->size] = value;
	v->size++;
	return (1);
}

type_bool_vec		bool_vec_pop(t_bool_vec *v)
{
	if (v->size)
	{
		v->size--;
		return (v->data[v->size]);
	}
	return (0);
}

int		bool_vec_cpy(t_bool_vec src, t_bool_vec *dst)
{
	int	i;

	if (src.size == 0)
	{
		*dst = bool_vec_init();
		return (1);
	}
	if (bool_vec_reserve(dst, src.size) == 0)
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

int			bool_vec_insert_one(t_bool_vec *v, int pos, type_bool_vec value)
{
	int	i;
	if (v->size == v->capacity)
	{
		if (v->capacity == 0 && bool_vec_reserve(v, 1) == 0)
			return (0);
		else if (bool_vec_reserve(v, v->capacity * 2) == 0)
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

int			bool_vec_resize(t_bool_vec *v, int new_size, type_bool_vec value)
{
	if (new_size < 0)
		return(1);
	else if (new_size <= v->size)
		v->size = new_size;
	else
	{
		if (new_size > v->capacity) {
			if (new_size < v.capacity * 2 && !bool_vec_reserve(v, v->capacity * 2))
				return (0);
			else if (new_size > v.capacity * 2 && !bool_vec_reserve(v, new_size))
				return (0);
		}
		while (--new_size >= v->size)
			v->data[new_size] = value;
		v->size = new_size;
	}
	return (1);
}

type_bool_vec			bool_vec_erase_one(t_bool_vec *v, int pos)
{
	type_bool_vec ret;

	ret = v->data[pos];
	--v->size;
	while (pos < v->size)
	{
		v->data[pos] = v->data[pos + 1];
		pos++;
	}
	return (ret);
}
