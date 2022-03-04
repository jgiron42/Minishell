//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

t_status	ft_shell(t_env *env, char *line)
{
	t_token_list	*tokens;
	t_command		tree;
	int				ret;

	if (tokenise(line, &tokens, env) != OK	)
	{
		free_token_list(tokens);
		if (env->is_interactive)
			return (KO);
		else
			return (FATAL);
	}
	if (tokens->type == END)
		return (OK);
	ret = parse_tree(tokens, &tree, env);
	if (ret == OK)
		ret = exec_command(tree, env);
	else if (!env->is_interactive)
		ret = FATAL;
	destroy_tree(tree);
	free_token_list(tokens);
	return (ret);
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
		set_signal(SIGINT, SIG_IGN, env);
		if (ret == OK && ft_shell(env, line) == FATAL)
		{
			free(line);
			return (FATAL);
		}
		set_signal(SIGINT, sigint_handler, env);
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
