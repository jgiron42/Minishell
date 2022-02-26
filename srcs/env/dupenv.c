//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

t_var_list *dup_var_list(t_var_list *src)
{
	t_var_list	*ret;
	t_var_list	*tmp;

	ret = NULL;
	while (src)
	{
		if (src->is_exported)
		{
			if (!ret)
			{
				if (add_var(&ret, src->key, src->value, true) == FATAL)
					return (NULL);
				ret = tmp;
			}
			else
			{
				if (add_var(&tmp->next, src->key, src->value, true) == FATAL) {
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