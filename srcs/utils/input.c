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

t_status	readnline(char **line, t_env *env)
{
	char *tmp;

	*line = my_readline(env, "PS1");
	if(!*line)
		ft_exit(env);
	if (!**line)
		return (KO);
	while ((*line)[ft_strlen(*line) - 1] == '\\')
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
