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
/*
 * A="coucou      ca "
 * B="va"
 * $A$B
 * coucou ca va
 */
t_status	loop(t_env *env)
{
	char	*line;

	while (1)
	{
		line = readline(get_var_val(env, "PS1"));
		if (!line)
			ft_exit(env);
		add_history(line);
		if (ft_shell(env, line) == FATAL)
		{
			free(line);
			clear_history();
			return (FATAL);
		}
		clear_history();
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
