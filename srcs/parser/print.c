#include "minishell.h"

void ft_print_pipe(t_pipeline **line);
void ft_print_grouping(t_grouping **line);
void ft_print_list(t_list **line);

void ft_print_pipe(t_pipeline **line)
{
	t_pipeline	*tmp;

	tmp = (*line);
	if (!tmp)
	{
		printf("empty\n");
		exit(3);
	}
	while (tmp)
	{
		if (tmp->command.type == SIMPLE)
		{
			ft_prin(&(tmp->command.command.simple.argv));
		}
		if (tmp->command.type == GROUPING)
		{
			ft_print_grouping(&(tmp->command.command.grouping));
		}
		tmp = tmp->next;
	}
}

void ft_print_list(t_list **line)
{
	t_list	*tmp;

	tmp = (*line);
	if (!tmp)
	{
		printf("empty list\n");
		exit(3);
	}
	while (tmp)
	{
		printf("Mon sparateur est le %d\n", tmp->sep);
		if (tmp->command.type == SIMPLE)
		{
			ft_prin(&(tmp->command.command.simple.argv));
		}
		if (tmp->command.type == PIPELINE)
		{
			ft_print_pipe(&(tmp->command.command.pipeline));
		}
		if (tmp->command.type == GROUPING)
		{
			ft_print_grouping(&(tmp->command.command.grouping));
		}
		tmp = tmp->next;
	}
}

void ft_print_grouping(t_grouping **line)
{
	t_grouping	*tmp;

	tmp = (*line);
	if (!tmp)
	{
		printf("empty list\n");
		exit(3);
	}
		if (tmp->command.type == SIMPLE)
		{
			ft_prin(&(tmp->command.command.simple.argv));
		}
		if (tmp->command.type == PIPELINE)
		{
			ft_print_pipe(&(tmp->command.command.pipeline));
		}
		if (tmp->command.type == LIST)
		{
			ft_print_list(&(tmp->command.command.list));
		}
			printf("-------redir------------\n");
			ft_prin_redir(&(tmp->redir_list));
}
