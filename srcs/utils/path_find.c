//
// Created by joachim on 26/02/2022.
//
#include "minishell.h"

t_status	path_find2(char **array, char *name, char **dst)
{
	t_status	ret;

	name = ft_strjoin("/", name);
	ret = KO;
	if (!name)
		ret = FATAL;
	while (*array)
	{
		*dst = ft_strjoin(*array, name);
		if (!*dst)
		{
			ret = FATAL;
			break;
		}
		if (!access(*dst, F_OK) && !is_dir(*dst))
		{
			ret = OK;
			break;
		}
		free(*dst);
		++array;
	}
	free(name);
	return (ret);
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
	if (ret == KO)
		*dst = NULL;
	return (ret);
}
