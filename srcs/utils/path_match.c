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
		else
			return (false);
	} while (*glob && (*str || *glob == '*'));
	return (*str == *glob);
}

t_status path_match_recurse(char *path, char **array, t_str_vec *dst)
{
	DIR				*current;
	struct dirent	*entry;
	char			*tmp;

	if (!*path)
		current = opendir(".");
	else
		current = opendir(path);
	if (!current)
		return (KO);
	entry = readdir(current);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..") && glob_include(*array, entry->d_name))
		{
			path_push(path, entry->d_name);
			if (is_dir(path) && array[1]) {
				path_match_recurse(path, array + 1, dst);
			}
			else if (!array[1])
			{
				printf("# %s\n", path);
				tmp = ft_strdup(path);
				if (!tmp || !str_vec_push(dst, tmp))
				{
					closedir(current);
					return (FATAL);
				}
			}
			path_pop(path);
		}
		entry = readdir(current);
	}
	closedir(current);
	return (OK);
}

char *path_match(char *str)
{
	char	**array;
	char	path[PATH_MAX];
	t_str_vec	dst;

	dst = str_vec_init();
	array = ft_split(str, '/');
	// TODO: protect
	if (*str == '/')
		ft_strcpy(path, "/");
	else
		ft_strcpy(path, ".");
	path_match_recurse(path,array, &dst);
	return ("");
}