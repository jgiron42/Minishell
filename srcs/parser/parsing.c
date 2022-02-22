#include "minishell.h"

//jo voie une fonction avec t_tokenlist list et valeur qui demande a retourner a parse
//

//	penser prorteger si nul etc ..

// 	fonction par struct: t_grouping / t_list / t_pipeline / t_simple / t_redir
// 	fonction redir
//	fonction here doc
//	prototype possible t_command *parsing(t_token_list *list,char *deliniter)

t_command ft_newcmd(enum e_command_type cmd_type, union u_command command)
{
	t_command *new;

	new = (t_command *)malloc(sizeof(t_command)));
	if (!new)
		return (NULL);
	new->type = cmd_type;
	new->command = command;
}

t_redir	new_redir_list(t_token_list **current)
{
	t_redir *new;

	new = (t_redir *)malloc(sizeof(t_redir)));
	if (!new)
		return (NULL);

	if (current->next && current->next->type == WORD)
	{
		current = current->next;
		current->word = current->arg;
	}
}
t_command *parse_simple(t_token_list **current)
{
	t_command	*tree;
	t_simple	simple;
	t_redir		*redir_list;

	redir_list = NULL;
	tree = ft_newcmd(SIMPLE, simple);
	if ((*current)->type = WORD)
		simple.argv = (*current);
	else
		redir_list = new_redir_list(current);
	simple.redir_list = redir_list;


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

t_command *parsing(t_token_list **current_token, t_token_type expected)
{
	t_command *tree;

	if ((*current) == NULL)
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
		// else if ((*current)->type == PIPE)
		// {
		// 	tree = parse_pipe();
		// }
		// else if ((*current)->type == OR_IF || (*current)->type == AND_IF)
		// {
		// 	tree = parse_list();
		// }
	}
	return (tree);
}
