/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 02:40:29 by ereali            #+#    #+#             */
/*   Updated: 2022/03/04 20:53:51 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	sh_exit(char **argv, t_env *env)
{
	int	i;

	i = 0;
	argv++;
	if (!(*argv))
		ft_exit(env);
	while (ft_isdigit((*argv)[i]))
		i++;
	if ((*argv)[i] == '\0'
		&& !(nb_is_superior(*argv, "9223372036854775807")))
		g_err = ft_atoi(*argv);
	else if ((i >= 20 || nb_is_superior(*argv, "9223372036854775807"))
		&& (*argv)[i] == '\0')
	{
		g_err = 2;
		return (ft_putstr_fd("exit : numeric argument required\n", 2),
			ft_exit(env), OK);
	}
	ft_exit(env);
	return (0);
}
