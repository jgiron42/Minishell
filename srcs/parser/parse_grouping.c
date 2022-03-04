#include "minishell.h"

t_grouping	*ft_new_grouping(t_command command)
{
	t_grouping	*new;

	new = (t_grouping *)malloc(sizeof(t_grouping));
	if (!new)
		return (NULL);
	new->is_in_subshell = 1;
	new->command = command;
	new->redir_list = NULL;
	return (new);
}

t_command	parse_grouping(t_token_list **current, t_env *env)
{
	t_command	tree;
	t_command	next;
	t_redir		*tmp;
	int			ret;

	tree = (t_command){.type = GROUPING};
	(*current) = (*current)->next;
	next = parsing(current, RPARENTHESIS, env);
	if ((*current) && (*current)->type != RPARENTHESIS)
	{
		destroy_tree(next);
		next.type = PARSE_ERROR;
	}
	if (next.type == PARSE_ERROR || next.type == PARSE_FATAL)
		return (parse_error((t_command[2]){}, next));
	tree.command.grouping = ft_new_grouping(next);
	if (!tree.command.grouping)
		return ((t_command){.type = PARSE_FATAL});
	(*current) = (*current)->next;
	while (*current && (*current)->type <= DGREAT && (*current)->type >= GREAT)
	{
		ret = new_redir_list(current, &tmp, env);
		if (ret != OK || !tmp)
			return (parse_error((t_command[2]){tree}, (t_command){.type = ret - 1 + PARSE_ERROR}));
		ft_lstadd_back_redir(&(tree.command.grouping->redir_list), tmp);
		(*current) = (*current)->next;
	}
	return (tree);
}
