#include "minishell.h"

t_list	*ft_new_list(t_command command, t_token_list *current)
{
	t_list	*new;

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

t_command	parse_list(t_token_list **current, t_command prev_command, t_env *env)
{
	t_command	tree;
	t_command	tmp_com;
	t_list		*tmp;

	tree.type = LIST;
	tree.command.list = ft_new_list(prev_command, *current);
	if (!tree.command.list)
		return (parse_error((t_command[2]){prev_command}, (t_command){.type = PARSE_FATAL}));
	tmp = tree.command.list;
	while (*current && ((*current)->type == AND_IF || (*current)->type == 128))
	{
		(*current) = (*current)->next;
		tmp_com	= parsing(current, AND_IF | 128 | 512 | END, env);
		if (tmp_com.type == PARSE_FATAL || tmp_com.type == PARSE_ERROR)
			return (parse_error((t_command[2]){tree}, tmp_com));
		tmp->next = ft_new_list(tmp_com, *current);
		if (!tmp->next)
			return (parse_error((t_command[2]){tree, tmp_com}, (t_command){.type = PARSE_FATAL}));
		tmp = tmp->next;
	}
	return (tree);
}
// printf("----------------LISTPRINT----------------\n");
// ft_print_list(&first);
// printf("----------------END----------------\n");
