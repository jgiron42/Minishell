#include "minishell.h"

t_pipeline *ft_new_pipe(t_command command)
{
	t_pipeline *new;

	new = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new)
		return (NULL);
	new->command = command;
	new->next = NULL;
	return (new);
}

t_command parse_pipe(t_token_list **current, t_command prev_command)
{
	t_command tree;
	t_pipeline *first;
	t_pipeline *tmp;

	// tree = ft_newcmd(PIPELINE);
	tree.type = PIPELINE;
	tree.command.pipeline = ft_new_pipe(prev_command);
	first = tree.command.pipeline;
	tmp = first;
	while ((*current) && (*current)->type == PIPE)
	{
		(*current) = (*current)->next;
		if (!(*current) || ((*current)->type > DGREAT && (*current)->type != LPARENTHESIS))
		{
			printf("\033[0;31merreur syntax: wrong token after pipe\n");
			exit(5);
		}
		tmp->next = ft_new_pipe(parsing(current, AND_IF | OR_IF | PIPE | RPARENTHESIS));
		tmp = tmp->next;
	}
	printf("----------------PIPEPRINT----------------\n");
	ft_print_pipe(&first);
	printf("----------------END----------------\n");

	return(tree);
}
