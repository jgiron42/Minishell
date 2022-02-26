#include "minishell.h"

int	add_var(t_env *env, char *key, char *value, bool is_exported)
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
	if (!env->vars)
		env->vars = new_node;
	else
	{
		tmp = env->vars;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (OK);
}

char	*get_var_val(t_env *env, char *key)
{
	while(env->vars)
	{
		if (!ft_strcmp(key, env->vars->key))
			return (env->vars->value);
		env->vars = env->vars->next;
	}
	return (NULL);
}

t_var_list		*get_var_ptr(t_env *env, char *key)
{
	while(env->vars)
	{
		if (!ft_strcmp(key, env->vars->key))
			return (env->vars);
		env->vars = env->vars->next;
	}
	return (NULL);
}

t_status		set_var(t_env *env, char *key, char *value, bool is_exported)
{
	t_var_list *tmp;

	tmp = env->vars;
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
	return (add_var(env, key, value, is_exported));
}

int 	remove_var(t_env *env, char *key)
{
	t_var_list *tmp;
	t_var_list *old;

	tmp = env->vars;
	old = NULL;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			free(tmp->key);
			free(tmp->value);
			if (!old)
				env->vars = tmp->next;
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
	t_var_list	*tmp;

	while (env->vars)
	{
		free(env->vars->key);
		free(env->vars->value);
		tmp = env->vars->next;
		free(env->vars);
		env->vars = tmp;
	}
	free(env->opened_files.data);
}

t_status	export_var(t_env *env, char *key)
{
	while(env->vars)
	{
		if (!ft_strcmp(key, env->vars->key))
		{
			env->vars->is_exported = true;
			return (OK);
		}
		env->vars = env->vars->next;
	}
	return (KO);
}