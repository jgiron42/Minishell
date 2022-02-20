//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	t_var_list	*env;

	if (parse_env(envp, &env) == FATAL || init_env(&env) == FATAL)
	{
		free_env(env);
		return (1);
	}
	// TEST:
	char **zbeub = serialize_env(env);
	for (int i = 0; zbeub[i]; ++i)
		printf("%s\n", zbeub[i]);
	free_env(env);
	ft_free_split(zbeub);
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