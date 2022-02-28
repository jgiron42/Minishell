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

t_command	parse_error(t_command to_destroy[2], t_command ret)
{
	destroy_tree(to_destroy[0]);
	destroy_tree(to_destroy[1]);
	return (ret);
}

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

void	free_redir(t_redir *list)
{
	if (!list)
		return;
	free_redir(list->next);
	free(list->word);
	free(list);
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
	bool		operator;

	tree = (t_command){.type = PARSE_ERROR};
	operator = false;
	if (!(*current))
		return (tree);
	while (!(expected & (*current)->type))
	{
		if (!operator && ((*current)->type >= WORD && (*current)->type <= DGREAT))
			tree = parse_simple(current);
		else if (!operator && (*current)->type == LPARENTHESIS)
			tree = parse_grouping(current);
		else if (operator && (*current)->type == PIPE)
			tree = parse_pipe(current, tree);
		else if (operator && ((*current)->type == OR_IF || (*current)->type == AND_IF))
			tree = parse_list(current, tree);
		else
		{
			destroy_tree(tree);
			return ((t_command){.type = PARSE_ERROR});
		}
		if (tree.type == PARSE_ERROR || tree.type == PARSE_FATAL)
			return (tree);
		operator = true;
	}
	return (tree);
}

const char 	*get_token_str(t_token_type token)
{
	int	i;
	const char *token_list[] = {
			"",
			">",
			"<",
			"<<",
			">>",
			"|",
			"&&",
			"||",
			"(",
			")",
			";",
			"end of line",
	};

	i = 0;
	while (token != 1)
	{
		token >>= 1;
		i++;
	}
	return (token_list[i]);
}

t_status 	parse_tree(t_token_list *current, t_command *tree, t_env *env)
{
	*tree = parsing(&current, END);
	if (tree->type == PARSE_FATAL)
		return (FATAL);
	else if (tree->type == PARSE_ERROR)
		return (my_perror(env, (char *[2]){"Syntax error near unexpected token: ",
   (char *)get_token_str(current->type)}, false, KO));
#ifdef DEBUGPARSING
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
#endif
	return (OK);
}
