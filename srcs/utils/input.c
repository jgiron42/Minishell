//
// Created by joachim on 27/02/2022.
//

#include "minishell.h"

char		*my_readline(t_env *env, char *prompt)
{
	if (!env->is_interactive)
		return (readline(NULL));
	return (readline(get_var_val(env, prompt)));
}

int		count_trailing_backslashes(char *str)
{
	size_t	i;
	int		ret;

	i = ft_strlen(str);
	ret = 0;
	while(i > 0)
	{
		if (str[i - 1] != '\\')
			break;
		++ret;
		--i;
	}
	return (ret);
}

t_status	readnline(char **line, t_env *env)
{
	char *tmp;

	*line = my_readline(env, "PS1");
	if(!*line)
		ft_exit(env);
	if (!**line)
		return (KO);
	while (count_trailing_backslashes(*line) % 2)
	{
		(*line)[ft_strlen(*line) - 1] = '\0';
		tmp = my_readline(env, "PS2");
		if (!tmp)
			break;
		if (*tmp)
			*line = ft_strjoinf1(*line, tmp);
		if (!*line)
			return (FATAL);
		free(tmp);
	}
	if (**line)
		add_history(*line);
	return (OK);
}
