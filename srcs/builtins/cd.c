/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 04:00:47 by ereali            #+#    #+#             */
/*   Updated: 2022/03/04 20:52:04 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	sh_cd(char **argv, t_env *env)
{
	char	*pathname;
	int		ret;

	argv++;
	if (!(*argv))
	{
		pathname = get_var_val(env, "HOME");
		if (!pathname)
			return (KO);
		pathname = ft_strdup(pathname);
		if (!pathname)
			return (FATAL);
	}
	else
		pathname = ft_strdup(*argv);
	if (!pathname)
		return (FATAL);
	if (chdir(pathname) < 0)
		return (my_perror(env, (char *[2]){"cd: can't cd to ", pathname},
			true, KO), free(pathname), KO);
	if (set_var(env, "PWD", pathname, 1))
		return (FATAL);
	return (free(pathname), OK);
}
// free path name ?
