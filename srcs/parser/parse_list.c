#include "minishell.h"

t_list *ft_new_list(t_command command, t_token_list *current)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (current && (current->type == OR_IF || current->type == AND_IF))
		new->sep = current->type;
	else
		new->sep = SEMI;
	new->command = command;
	new->next = NULL;
	return (new);
}



t_command parse_list(t_token_list **current, t_command prev_command)
{
	t_command tree;
	t_list	*first;
	t_list	*tmp;

	tree.type = LIST;
	tree.command.list = ft_new_list(prev_command, *current);
	first = tree.command.list;
	tmp = first;
	while ((*current) && ((*current)->type == AND_IF || (*current)->type == OR_IF ))
	{
		(*current) = (*current)->next;
		if (!(*current) || ((*current)->type > DGREAT && (*current)->type != LPARENTHESIS))
		{
			printf("\033[0;31merreur syntax: wrong token after list\n");
			exit(5);
		}
		tmp->next = ft_new_list(parsing(current, AND_IF | OR_IF| RPARENTHESIS ), *current);
		tmp = tmp->next;
	}
	// printf("----------------LISTPRINT----------------\n");
	// ft_print_list(&first);
	// printf("----------------END----------------\n");

	return (tree);
}
