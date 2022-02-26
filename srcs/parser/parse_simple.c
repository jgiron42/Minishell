#include "minishell.h"

void	ft_lstadd_back(t_token_list **alst, t_token_list *new)
{
	t_token_list	*tmp;

	if (!(*alst))
	{
		(*alst) = new;
		new->next = NULL;
	}
	else if (new)
	{
		tmp = (*alst);
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->next = NULL;
	}
}

t_command parse_simple(t_token_list **current)
{
	t_command	tree;
	t_token_list *cpy;

	// tree = ft_newcmd(SIMPLE);
	tree = (t_command){};
	tree.type = SIMPLE;
	tree.command.simple.argv = NULL;
	while ((*current) && (*current)->type >= WORD && (*current)->type <= DGREAT)
	{
		cpy = ft_lstcpy(*current);
		if ((*current)->type == WORD)
			ft_lstadd_back(&(tree.command.simple.argv), cpy);
		else
			ft_lstadd_back_redir(&tree.command.simple.redir_list, new_redir_list(current));
		(*current) = (*current)->next;
	}
	return (tree);
}
