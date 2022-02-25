#include "minishell.h"

t_grouping *ft_new_grouping(t_command command)
{
	t_grouping *new;

	new = (t_grouping *)malloc(sizeof(t_grouping));
	if (!new)
		return (NULL);
	new->is_in_subshell = 1;
	new->command = command;
	new->redir_list = NULL;
	return (new);
}

t_command parse_grouping(t_token_list **current)
{
	t_command tree;

	// tree = ft_newcmd(PIPELINE);
	tree = (t_command){};
	tree.type = GROUPING;
	(*current) = (*current)->next;
	if (!(*current) || ((*current)->type > DGREAT && (*current)->type < LPARENTHESIS))
	{
		printf("\033[0;31merreur syntax: wrong token after parenthesis\n");
		exit(5);
	}
	tree.command.grouping = ft_new_grouping(parsing(current, RPARENTHESIS));
	if (!current)
	{
		printf("\033[0;31merreur syntax: no closing parenthesis\n");
		exit(5);
	}
	else
		(*current) = (*current)->next;
	while ((*current) && (*current)->type <= DGREAT && (*current)->type >= GREAT)
	{
		ft_lstadd_back_redir(&(tree.command.grouping->redir_list), new_redir_list(current));
		(*current) = (*current)->next;
	}
	// if (*current)
	// 	printf("last arg %s\n", (*current)->arg);

	printf("----------------GROUPINGPRINT----------------\n");
	ft_print_grouping(&(tree.command.grouping));
	printf("----------------END----------------\n");
	return(tree);
}
