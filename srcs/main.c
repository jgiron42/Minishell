//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

t_status	ft_shell(t_env *env, char *line)
{
	t_token_list	*tokens;
	t_command		tree;
	int				ret;

	if (tokenise(line, &tokens) == FATAL)
		return (FATAL);
	if (!tokens)
		return (OK);
	ret = parse_tree(tokens, &tree);
	if (ret != OK)
	{
		//TODO: destroy_token_list(tokens)
		return (ret);
	}
	return (exec_command(tree, env));
}

t_status	readnline(char **line, t_env *env)
{
	char *tmp;

	*line = readline(get_var_val(env, "PS1"));
	if(!*line)
		ft_exit(env);
	if (!**line)
		return (KO);
	while ((*line)[ft_strlen(*line) - 1] == '\\')
	{
		(*line)[ft_strlen(*line) - 1] = '\0';
		tmp = readline(get_var_val(env, "PS2"));
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

t_status	loop(t_env *env)
{
	char	*line;
	int		ret;

	while (1)
	{
		ret = readnline(&line, env);
		if (ret == FATAL)
			return (FATAL);
		if (ret == OK && ft_shell(env, line) == FATAL)
		{
			free(line);
			return (FATAL);
		}
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env		env;

	(void)argc;
	(void)argv;
	if (parse_env(envp, &env) != FATAL && init_env(&env) != FATAL)
		loop(&env);
	perror(NAME);
	free_env(&env);
	return (1);
}

/* ( ls | cat && pwd || ls ) | { pwd | echo } && ls
 *
 *
 *
 * 		ls		  cat
 * 		|		  |
 * 		pipeline--pl     pwd	   ls	   pwd		   echo
 * 		|				 |		   |	   |		   |
 * 		list&&-----------list||----list;   pipeline----pl
 * 		|								   |
 * 		grouping(						   grouping{
 * 		|								   |
 * 		pipeline---------------------------pl				 ls
 * 	   	|				   									 |
 * 		list&&-----------------------------------------------list;
 * 		|
 * 		root
 */
//
//t_command	*parse_grouping(t_token *list)
//{
//	 t_command *ret = new_command;
//
//	 if (list->type == '(')
//		 new_command->is_in_subshell = true;
//	 else
//		 new_command->is_in_subshell = false;
//	 ret->command = parse(list->next, {')'});
//	 return (ret);
//}
//	pipeline: {"|", "&&", "||", ")"};
//	list:	  {"&&", "||", ")"};
//	simple:	  {"|", "&&", "||", ")"};
//	grouping: {")"};
//
//root = parse(token_list);
