//
// Created by joachim on 21/11/2021.
//
#include "minishell.h"

static char *join_key_value(char *key, char *value)
{
	char *ret;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!ret)
		return (NULL);
	while (*key)
	{
		ret[i++] = *key;
		++key;
	}
	ret[i++] = '=';
	while (*value)
	{
		ret[i++] = *value;
		++value;
	}
	ret[i] = 0;
	return (ret);
}

static size_t	get_env_size(t_env *env)
{
	size_t	ret;

	ret = 1;
	while(env)
	{
		env = env->next;
		ret++;
	}
	return (ret);
}

char **serialize_env(t_env *env)
{
	ssize_t	i;
	t_env	*tmp;
	char	**ret;

	tmp = env;
	ret = malloc((1 + get_env_size(env)) * sizeof(char *));
	i = 0;
	if (!ret)
		return (NULL);
	while (env)
	{
		if (env->is_exported)
			ret[i] = join_key_value(env->key, env->value);
		if (env->is_exported && !ret[i++])
		{
			while (i > 0)
				free(ret[i--]);
			free(ret);
			return (NULL);
		}
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}