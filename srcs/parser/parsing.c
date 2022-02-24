#include "minishell.h"

//jo voie une fonction avec t_tokenlist list et valeur qui demande a retourner a parse
//

//	penser prorteger si nul etc ..
// fonction check type puis print en fct
// 	fonction par struct: t_grouping / t_list / t_pipeline
//	fonction here doc
//	prototype possible t_command *parsing(t_token_list *list,char *deliniter)

t_command *ft_newcmd(enum e_command_type cmd_type)
{
	t_command *new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->type = cmd_type;
	return (new);
}

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
		printf("ERROR: invalid token after redirection\n");
		exit(4);
	}
	return (new);
}

t_command *parse_simple(t_token_list **current)
{
	t_command	*tree;
	t_token_list *cpy;

	tree = ft_newcmd(SIMPLE);
	tree->command.simple.argv = NULL;
	while ((*current) && (*current)->type >= WORD && (*current)->type <= DGREAT)
	{
		cpy = ft_lstcpy(*current);
		if ((*current)->type == WORD)
			ft_lstadd_back(&(tree->command.simple.argv), cpy);
		else
			ft_lstadd_back_redir(&tree->command.simple.redir_list, new_redir_list(current));
		(*current) = (*current)->next;
	}
	return (tree);
}

//
// t_command *parse_grouping(t_token_list **current)
// {
// 	t_command *tree;
//
// 	tree = ft_newcmd(GROUPING);
// }
//
// t_command *parse_pipe(t_token_list **current)
// {
// 	t_command *tree;
//
// 	tree = ft_newcmd(PIPELINE);
// }
//
// t_command *parse_list(t_token_list **current)
// {
// 	t_command *tree;
//
// 	tree = ft_newcmd(LIST);
// }
// t_command *parsing(t_token_list **current_token, t_command *tree, t_token_type expected)

t_command *parsing(t_token_list **current, t_token_type expected)
{
	t_command *tree;

	tree = NULL;
	if (!(*current))
		return (tree);
	if ((*current)->type != LPARENTHESIS && (*current)->type < WORD && (*current)->type > DGREAT)
	{
		printf("Wrong syntax token");
		exit(1);
	}
	while ((*current) && !(expected & (*current)->type))
	{
		if ((*current)->type >= WORD && (*current)->type <= DGREAT)
		{
			tree = parse_simple(current);
		}
		// else if ((*current)->type == LPARENTHESIS)
		// {
		// 	tree = parse_grouping();
		// }
		else if ((*current)->type == PIPE)
		{
			tree = parse_pipe();
		}
		// else if ((*current)->type == OR_IF || (*current)->type == AND_IF)
		// {
		// 	tree = parse_list();
		// }
		printf("Je suis passer dans la boucle de parsing\n" );
	}
	printf("Je suis passer dans parsing\n");
	return (tree);
}
