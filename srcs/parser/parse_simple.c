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

t_command	parse_simple(t_token_list **current)
{
	t_command		tree;
	t_token_list	*cpy;
	t_redir			*tmp;
	int				ret;

	tree = (t_command){.type = SIMPLE};
	while ((*current) && (*current)->type >= WORD && (*current)->type <= DGREAT)
	{
		if ((*current)->type == WORD)
		{
			cpy = ft_lstcpy(*current);
			if (!cpy)
				return (parse_error((t_command[2]){tree}, (t_command){.type = PARSE_FATAL}));
			ft_lstadd_back(&(tree.command.simple.argv_tokens), cpy);
		}
		else
		{
			ret = new_redir_list(current, &tmp);
			if (ret != OK || !tmp)
				return(parse_error((t_command[2]){tree}, (t_command){.type = ret - 1 + PARSE_ERROR}));
			ft_lstadd_back_redir(&tree.command.simple.redir_list, tmp);
		}
		(*current) = (*current)->next;
	}
	return (tree);
}
