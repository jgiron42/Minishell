//
// Created by joachim on 27/02/2022.
//

#include "minishell.h"

bool glob_include(char * glob, char * str)
{
	do {
		if (*glob == '*')
		{
			while (*glob == '*')
				++glob;
			if (!*glob)
				return true;
			while (*str) {
				if ((*glob == *str || *glob == '?') && glob_include(glob, str))
					return true;
				++str;
			}
			return false;
		}
		else if (*glob && (*glob == '?' || *glob == *str))
		{
			++str;
			++glob;
		}
	} while (*glob && (*str || *glob == '*'));
	return (*str == *glob);
}

t_status path_match_recurse(char *path, char **array, t_str_vec *dst)
{
	DIR				*current;
	struct dirent	*entry;
	char			*tmp;

	current = opendir(path);
	if (!current)
		return (KO);
	entry = readdir(current);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..") && glob_include(*array, entry->d_name))
		{
			path_push(path, *array);
			if (is_dir(path))
				path_match_recurse(path, array + 1, dst);
			else if (!array[1])
			{
				tmp = ft_strdup(path);
				if (!tmp || !str_vec_push(dst, tmp))
					return (FATAL);
			}
			path_pop(path);
		}
		entry = readdir(current);
	}
	return (OK);
}

char *path_match(char *str)
{
	char	**path;
	char	tmp[PATH_MAX];
	t_str_vec	dst;

	dst = str_vec_init();
	path = ft_split(str, '/');
	// TODO: protect
	if (*str == '/')
		ft_strcpy(tmp, "");
	else
		ft_strcpy(tmp, ".");
	path_match_recurse(tmp, path, &dst);
	return (NULL);
}