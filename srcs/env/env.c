#include "minishell.h"

int	add_env(t_env **env, char *key, char *value, bool is_exported)
{
	t_env *new_node;
	t_env *tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (SYSCALL_FAILURE);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->is_exported = is_exported;
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		return (SYSCALL_FAILURE);
	}
	new_node->value = ft_strdup(value);
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

char	*get_env(t_env *env, char *key)
{
	while(env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_status		set_env(t_env **env, char *key, char *value, bool is_exported)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			free(tmp->value);
			tmp->value = value;
			return (OK);
		}
		tmp = tmp->next;
	}
	return (add_env(env, key, value, is_exported));
}

int 	remove_env(t_env **	env, char *key)
{
	t_env *tmp;
	t_env *old;

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

void free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}
