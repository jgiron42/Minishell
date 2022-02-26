//
// Created by joachim on 26/02/2022.
//
#include "minishell.h"

t_status	path_find2(char **array, char *name, char **dst)
{
	name = ft_strjoinf2("/", name);
	if (!name)
		return (FATAL);
	while (*array)
	{
		*dst = ft_strjoin(*array, name);
		if (!*dst)
			return (FATAL);
		if (!access(*dst, F_OK))
			return (OK);
		free(*dst);
		++array;
	}
	return (KO);
}

t_status	path_find(char *name, t_env *env, char **dst)
{
	char **directories;
	char	*path;
	int 	ret;

	path = get_var_val(env, "PATH");
	if (!path)
		return (KO);
	directories = ft_split(path, ':');
	if (!directories)
		return (FATAL);
	ret = path_find2(directories, name, dst);
	ft_free_split(directories);
	return (ret);
}
