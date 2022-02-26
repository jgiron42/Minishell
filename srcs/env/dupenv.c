//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

t_var_list *dup_var_list(t_var_list *src)
{
	t_env	ret;

	ret.vars = NULL;
	while (src)
	{
		if (src->is_exported)
		{
			if (add_var(&ret, src->key, src->value, true) == FATAL)
				return (NULL);
		}
		src = src->next;
	}
	return (ret.vars);
}