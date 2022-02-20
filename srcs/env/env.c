#include "minishell.h"

int	add_env(t_var_list **env, char *key, char *value, bool is_exported)
{
	t_var_list *new_node;
	t_var_list *tmp;

	new_node = malloc(sizeof(t_var_list));
	if (!new_node)
		return (FATAL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->is_exported = is_exported;
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		return (FATAL);
	}
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (OK);
}

char	*get_env_val(t_var_list *env, char *key)
{
	while(env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_var_list		*get_env_ptr(t_var_list *env, char *key)
{
	while(env)
	{
		if (!ft_strcmp(key, env->key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_status		set_env(t_var_list **env, char *key, char *value, bool is_exported)
{
	t_var_list *tmp;

	tmp = *env;
	while(tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			if (value == tmp->value)
				return (OK);
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (OK);
		}
		tmp = tmp->next;
	}
	return (add_env(env, key, value, is_exported));
}

int 	remove_env(t_var_list **	env, char *key)
{
	t_var_list *tmp;
	t_var_list *old;

	tmp = *env;
	old = NULL;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			free(tmp->key);
			free(tmp->value);
			if (!old)
				*env = tmp->next;
			else
				old->next = tmp->next;
			return (OK);
		}
		old = tmp;
		tmp = tmp->next;
	}
	return (KO);
}

void free_env(t_var_list *env)
{
	t_var_list	*tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}

t_status	export_env(t_var_list *env, char *key)
{
	while(env)
	{
		if (!ft_strcmp(key, env->key))
		{
			env->is_exported = true;
			return (OK);
		}
		env = env->next;
	}
	return (KO);
}