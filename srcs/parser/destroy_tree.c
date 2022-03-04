#include "minishell.h"

typedef void	(*t_command_destructor)(union u_command c);

//TODO

void	destroy_simple(union u_command c)
{
	free(c.simple.argv);
	free_token_list(c.simple.argv_tokens);
	free_redir(c.simple.redir_list);
	if (c.simple.argv)
		ft_free_split(c.simple.argv);
}

void	destroy_pipeline(union u_command c)
{
	if (!c.pipeline)
		return ;
	destroy_tree(c.pipeline->command);
	destroy_pipeline((union u_command){.pipeline = c.pipeline->next});
	free(c.pipeline);
}

void	destroy_list(union u_command c)
{
	if (!c.list)
		return ;
	destroy_tree(c.list->command);
	destroy_list((union u_command){.list = c.list->next});
	free(c.list);
}

void	destroy_grouping(union u_command c)
{
	destroy_tree(c.grouping->command);
	free_redir(c.grouping->redir_list);
	free(c.grouping);
}

void	destroy_tree(t_command c)
{
	const t_command_destructor	a[] = {&destroy_simple,
		&destroy_pipeline, &destroy_list, &destroy_grouping};

	if (c.type <= 3)
		a[c.type](c.command);
}
