/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:40:57 by jgiron            #+#    #+#             */
/*   Updated: 2022/03/04 11:54:20 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	glob_include(char *glob, char *str);

static char	manage_glob(char **glob, char **str, bool escaped)
{
	if (**glob == '*' && !escaped)
	{
		while (**glob == '*')
			++*glob;
		if (!**glob)
			return (true);
		while (**str && **str != '/')
		{
			if ((**glob == **str || **glob == '?') && glob_include(*glob, *str))
				return (true);
			++*str;
		}
		return (false);
	}
	else if (**glob && ((**glob == '?' && **str != '/' && !escaped)
			|| **glob == **str))
	{
		++*str;
		++*glob;
	}
	else
		return (false);
	return (-1);
}

bool	glob_include(char *glob, char *str)
{
	t_quote	state;
	bool	escaped;
	int		ret;

	state = NONE;
	escaped = false;
	if (*glob == '.' && *str != '.')
		return (false);
	if (*glob != '.' && *str == '.')
		return (false);
	do
	{
		if (escaped)
			escaped = (false);
		else if (*glob == '\'')
			state = (state != ONE) * ONE;
		else if (*glob == '"')
			state = (state != DOUBLE) * DOUBLE;
		else if (*glob == '\\')
		{
			escaped = true;
			++glob;
		}
		if (state == NONE || escaped)
		{
			ret = manage_glob(&glob, &str, escaped);
			if (ret != -1)
				return (ret);
		}
//		str++;
	} while (*glob && (*str || *glob == '*'));
	return (*str == *glob);
}

t_status path_match_recurse(char *path, char **array, t_str_vec *dst)
{
	DIR				*current;
	struct dirent	*entry;
	char			*tmp;

	while (!**array)
	{
		path_push(path, *array);
		++array;
	}
	if (!*path)
		current = opendir(".");
	else
	{
		// printf("-> %s\n", path);
		current = opendir(path);
	}
	if (!current)
		return (KO);
	entry = readdir(current);
	while (entry)
	{
		if (!ft_strcmp (entry->d_name, *array) ||
		(ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..")
		&& glob_include(*array, entry->d_name)))
		{
			path_push(path, entry->d_name);
			if (is_dir(path) && array[1])
				path_match_recurse(path, array + 1, dst);
			else if (!array[1])
			{
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

t_status	path_match(char *str, t_str_vec *dst)
{
	char	**array;
	char	path[PATH_MAX];
	int		tmpsize;
	int		ret;

	array = ft_split(str, '/');
	if (!array)
		return (FATAL);
	for (int i = 0; array[i]; i++)
		// printf("==> %s\n", array[i]);
		if (*str == '/')
			ft_strcpy(path, "/");
		else
			ft_strcpy(path, "");
	tmpsize = dst->size;
	ret = OK;
//	if (*array)
//		ret = path_match_recurse(path, array + (*str == '/'), dst);
	if (dst->size == tmpsize && ret != FATAL)
	{
		str = ft_strdup(str);
		if (!str)
			return (FATAL);
		str_vec_push(dst, str);
	}
	ft_free_split(array);
	return (ret);
}

t_status	path_match_current(char *glob, t_str_vec *dst)
{
	DIR				*current;
	struct dirent	*entry;
	char			*tmp;

	current = opendir(".");
	if (!current)
		return (KO);
	entry = readdir(current);
	while (entry)
	{
		if ((ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..")
				&& glob_include(glob, entry->d_name)))
		{
			tmp = ft_strdup(entry->d_name);
			if (!tmp || !str_vec_push(dst, tmp))
			{
				closedir(current);
				return (FATAL);
			}
		}
		entry = readdir(current);
	}
	closedir(current);
	return (OK);
}
