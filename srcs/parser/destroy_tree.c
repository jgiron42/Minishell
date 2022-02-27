#include "minishell.h"
typedef	void (*t_command_destructor)(union u_command c);

//TODO

void destroy_simple(union u_command c)
{
	(void)c;
}
void destroy_pipeline(union u_command c)
{
	(void)c;
}
void destroy_list(union u_command c)
{
	(void)c;
}
void destroy_grouping(union u_command c)
{
	(void)c;
}
void destroy_tree(t_command c)
{
	t_command_destructor a[] = {
			&destroy_simple,
			&destroy_pipeline,
			&destroy_list,
			&destroy_grouping
	};

	return(a[c.type](c.command));
}
