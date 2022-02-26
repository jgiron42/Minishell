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

void		ft_lstadd_back_redir(t_redir **alst, t_redir *new)
{
	t_redir	*tmp;

	if (!(*alst))
	{
		(*alst) = new;
		new->next = NULL;
	}
	else if (new)
	{
		tmp = (*alst);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
}

t_redir	*new_redir_list(t_token_list **current)
{
	t_redir *new;
	t_token_list *cpy;

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

t_status 	parse_tree(t_token_list *current, t_command *tree)
{
	*tree = parsing(&current, END);
	if (tree->type == PARSE_FATAL)
	{
		destroy_tree(*tree);
		return (FATAL);
	}
	else if (tree->type == PARSE_ERROR || (current &&current->type != END))
	{
		printf("parse error token %d", current->type);

		//TODO : parse_error((*current)->type)
		return (KO);
	}
	if (tree->type == SIMPLE)
	 {
	 	if (tree->command.simple.argv)
	 	{
	 		printf("-----------------argv---------------------\n" );
	 		ft_prin(&(tree->command.simple.argv_tokens));
	 		printf("---------------END------------\n" );
	 	}
	 	// printf("-------redir------------\n");
	 	// ft_prin_redir(&(tree.command.simple.redir_list));
	 }
	return (OK);
}
