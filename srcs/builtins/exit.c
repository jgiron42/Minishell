/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 02:40:29 by ereali            #+#    #+#             */
/*   Updated: 2022/03/04 11:22:37 by jgiron           ###   ########.fr       */
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
	if ((*argv)[i] == '\0')
		g_err = ft_atoi(*argv);
	ft_exit(env);
	return (0);
}
