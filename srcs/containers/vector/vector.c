
#include "NAME.h"

t_NAME	NAME_init()
{
	return ((t_NAME){});
}

int			NAME_reserve(t_NAME *v, int new_cap)
{
	type	*tmp;

	if (new_cap < v->capacity)
		return (1);
	tmp = malloc(sizeof(type) * new_cap);
	if (!tmp)
		return (0);
	v->data = tmp;
	v->capacity = new_cap;
	return (1);
}

int			NAME_push(t_NAME *v, type value)
{
	if (v->size <= v->capacity)
	{
		if (v->capacity == 0 && NAME_reserve(v, 1) == 0)
			return (0);
		else if (NAME_reserve(v, v->capacity * 2) == 0)
			return (0);
	}
	v->data[v->size] = value;
	v->size++;
	return (1);
}

type		NAME_pop(t_NAME *v)
{
	if (v->size)
	{
		v->size--;
		return (v->data[v->size]);
	}
	return (0);
}

int		NAME_cpy(t_NAME src, t_NAME *dst)
{
	int	i;

	if (src.size == 0)
	{
		*dst = NAME_init();
		return (1);
	}
	if (NAME_reserve(dst, src.size) == 0)
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

int			NAME_insert_one(t_NAME *v, int pos, type value)
{
	int	i;
	if (v->size <= v->capacity)
	{
		if (v->capacity == 0 && NAME_reserve(v, 1) == 0)
			return (0);
		else if (NAME_reserve(v, v->capacity * 2) == 0)
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

type			NAME_erase_one(t_NAME *v, int pos)
{
	type ret;

	ret = v->data[pos];
	--v->size;
	while (pos < v->size)
	{
		v->data[pos] = v->data[pos + 1];
		pos++;
	}
	return (ret);
}
