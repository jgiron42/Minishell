/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:41:16 by jgiron            #+#    #+#             */
/*   Updated: 2022/03/04 11:41:19 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_field_end(char *str, char *ifs)
{
	int	i;

	i = 0;
	while (ft_strchr(ifs, str[i]))
		++i;
	return (i);
}

int	get_field_start(char *str, char *ifs)
{
	int	i;

	i = 0;
	while (!ft_strchr(ifs, str[i]) || (ft_strchr(" \t\n", str[i]) && ft_strchr(" \t\n", str[i + 1])))
		++i;
	return (i);
}

t_str_vec ft_split_ifs(char *str, t_env *env)
{
	char		*ifs;
	t_str_vec	ret;

	ret = str_vec_init();
	ifs = get_var_val(env, "IFS");
	if (!ifs)
		ifs = " \t\n";
	if (*ifs == 0)
	{
		str_vec_push(&ret, ft_strdup(str));
		return (ret);
	}
	return (ret);
}
