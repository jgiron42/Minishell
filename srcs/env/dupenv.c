//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

t_env *dupenv(t_env *src)
{
	t_env	*ret;
	t_env	*tmp;

	ret = NULL;
	while (src)
	{
		if (src->is_exported)
		{
			if (!ret)
			{
				if (add_env(&ret, src->key, src->value, true) == FATAL)
					return (NULL);
				ret = tmp;
			}
			else
			{
				if (add_env(&tmp->next, src->key, src->value, true) == FATAL) {
					free_env(ret);
					return (NULL);
				}
				tmp = tmp->next;
			}
		}
		src = src->next;
	}
	return (ret);
}