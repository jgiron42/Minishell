//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

bool	path_has_dot(char *path)
{
	int dots;

	dots = 0;
	while(*path)
	{
		if (*path == '/')
		{
			if (/*dots == 0 ||*/dots == 1 || dots == 2)
				return (1);
			dots = 0;
		}
		else if (*path == '.' && dots != -1)
			++dots;
		else
			dots = -1;
		++path;
	}
	return (0);
}

t_status path_push(char *path, char *component)
{
	if (ft_strlen(path) + ft_strlen(component) + 1 >= PATH_MAX || ft_strlen(component) > NAME_MAX)
	{
		errno = ENAMETOOLONG;
		return (KO);
	}
	path += ft_strlen(path);
	if (path[-1] != '/')
	{
		*path = '/';
		++path;
	}
	while (*component)
	{
		*path = *component;
		++path;
		++component;
	}
	*path = 0;
	return (OK);
}

void path_pop(char *path)
{
	char *tmp;

	if (!path)
		return;
	tmp = path + ft_strlen(path);
	while (--tmp != path && *tmp != '/')
		;
	*tmp = 0;
}

static	t_status compute_path(char *current, char **splitted) {
	struct stat statbuf;
	char		buf[NAME_MAX + 1];
	ssize_t 		ret;
	int				link;

	link = 0;
#ifdef LINK_MAX
	while(*splitted && link < LINK_MAX)
#else
	while(*splitted)
#endif
	{
		if (!ft_strcmp(*splitted, ".."))
			path_pop(current);
		else if (ft_strcmp(*splitted, "."))
		{
			if (path_push(current, *splitted) == KO)
				return (KO);
			lstat(current, &statbuf);
//			printf("=========|||\n");
			if (S_ISLNK(statbuf.st_mode))
			{
				ret = readlink(current, buf, NAME_MAX);
				if (ret <= 0)
					return (KO);
				link++;
				buf[ret] = 0;
				if (*buf != '/')
				{
					path_pop(current);
					path_push(current, buf);
				}
				else
					ft_strcpy(current, buf);
				return (OK);
			}
//			printf("=========>> %s\n", current);

		}
		++splitted;
	}
	return (OK);
}

char 	*ft_realpath(const char *path, char *resolved_path)
{
	char	current[PATH_MAX];
	char	**splited;

	if (!path)
	{
		errno = EINVAL;
		return (NULL);
	}
	if (ft_strlen(path) >= PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return (NULL);
	}
	splited = ft_split(path, '/');
	if (!splited)
		return (NULL);
	current[0] = 0;
	if (compute_path(current, splited) == KO)
	{
		ft_free_split(splited);
		return (NULL);
	}
	ft_free_split(splited);
	if (!resolved_path)
		return(ft_strdup(current));
	ft_strcpy(resolved_path, current);
	return (resolved_path);
}
