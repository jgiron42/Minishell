#include "minishell.h"

t_pipeline	*ft_new_pipe(t_command command)
{
	t_pipeline	*new;

	new = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new)
		return (NULL);
	new->command = command;
	new->next = NULL;
	return (new);
}

t_command	parse_pipe(t_token_list **current, t_command prev_command)
{
	t_command	tree;
	t_command	tmp_c;
	t_pipeline	*first;
	t_pipeline	*tmp;

	tree.type = PIPELINE;
	tree.command.pipeline = ft_new_pipe(prev_command);
	first = tree.command.pipeline;
	tmp = first;
	while ((*current) && (*current)->type == PIPE)
	{
		(*current) = (*current)->next;
		if (!(*current) || ((*current)->type > 16 && (*current)->type != 256))
		{
			printf("\033[0;31merreur syntax: wrong token after pipe\n");
			exit(5);
		}
		tmp_c = parsing(current, 64 | 128 | PIPE | 512 | END);
		// if (tmp_c.type == 0)
		// 	return ()
		tmp->next = ft_new_pipe(tmp_c);
		tmp = tmp->next;
	}
	return (tree);
}
//	printf("----------------PIPEPRINT----------------\n");
//	ft_print_pipe(&first);
//	printf("----------------END----------------\n");
