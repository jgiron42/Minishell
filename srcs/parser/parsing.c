#include "minishell.h"

//	penser prorteger si nul etc ..
//	fonction here doc
//
// t_command *ft_newcmd(type)
// {
// 	t_command *new;
//
// 	new = (t_command *)malloc(sizeof(t_command));
// 	if (!new)
// 		return (NULL);
// 	new->type = cmd_type;
// 	return (new);
// }
void ft_print_pipe(t_pipeline **line);
void ft_print_grouping(t_grouping **line);
void ft_print_list(t_list **line);

t_redir	*new_redir_list(t_token_list **current)
{
	t_redir *new;
	t_token_list *cpy;

	printf("je suis passer dans redir\n" );
	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->newfd = 0;
	new->word = NULL;
	new->type = 0;
	if((*current)->type == LESS)
		new->type = INPUT;
	else if ((*current)->type == GREAT)
		new->type = OUTPUT;
	else if ((*current)->type == DGREAT)
		new->type = APPEND;
	else
		new->type = HERE;
	if((*current)->arg[0] == '>')
		new->newfd = 1;
	if ((*current)->next && (*current)->next->type == WORD)
	{
		(*current) = ((*current)->next);
		cpy = ft_lstcpy(*current);
		new->word = (cpy)->arg;
	}
	else
	{
		printf("\033[0;31mERROR: invalid token after redirection\n");
		exit(4);
	}
	return (new);
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

t_pipeline *ft_new_pipe(t_command command)
{
	t_pipeline *new;

	new = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new)
		return (NULL);
	new->command = command;
	new->next = NULL;
	return (new);
}

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

t_command parse_pipe(t_token_list **current, t_command prev_command)
{
	t_command tree;
	t_pipeline *first;
	t_pipeline *tmp;

	// tree = ft_newcmd(PIPELINE);
	tree.type = PIPELINE;
	tree.command.pipeline = ft_new_pipe(prev_command);
	first = tree.command.pipeline;
	tmp = first;
	while ((*current) && (*current)->type == PIPE)
	{
		(*current) = (*current)->next;
		if (!(*current) || ((*current)->type > DGREAT && (*current)->type != LPARENTHESIS))
		{
			printf("\033[0;31merreur syntax: wrong token after pipe\n");
			exit(5);
		}
		tmp->next = ft_new_pipe(parsing(current, AND_IF | OR_IF | PIPE | RPARENTHESIS));
		tmp = tmp->next;
	}
	printf("----------------PIPEPRINT----------------\n");
	ft_print_pipe(&first);
	printf("----------------END----------------\n");

	return(tree);
}

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

t_command parsing(t_token_list **current, t_token_type expected)
{
	t_command tree;

	tree = (t_command){};
	if (!(*current))
		return (tree);
	if ((*current)->type != LPARENTHESIS && (*current)->type < WORD && (*current)->type > DGREAT)
	{
		printf("\033[0;31mWrong syntax token\n");
		exit(1);
	}
	while ((*current) && !(expected & (*current)->type))
	{
		if ((*current)->type >= WORD && (*current)->type <= DGREAT)
			tree = parse_simple(current);
		else if ((*current)->type == LPARENTHESIS)
			tree = parse_grouping(current);
		else if ((*current)->type == PIPE)
			tree = parse_pipe(current, tree);
		else if ((*current)->type == OR_IF || (*current)->type == AND_IF)
			tree = parse_list(current, tree);
		else if ((*current)->type == RPARENTHESIS)
		{
			printf("\033[0;31mWrong syntax token\n");
			break;
		}
	}
	return (tree);
}
