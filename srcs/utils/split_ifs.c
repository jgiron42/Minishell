//
// Created by joachim on 2/7/22.
//
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
	ifs = get_env_val(env, "IFS");
	if (!ifs)
		ifs = " \t\n";
	if (*ifs == 0)
	{
		str_vec_push(&ret, ft_strdup(str));
		return (ret);
	}

}