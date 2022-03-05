#include "minishell.h"

//	penser prorteger si nul etc ..
//	fonction here doc

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

t_status	new_redir_list(t_token_list **current, t_redir **dst, t_env *env)
{
	*dst = (t_redir *)malloc(sizeof(t_redir));
	if (!*dst)
		return (FATAL);
	**dst = (t_redir){.fd_save = -1};
	if((*current)->type == LESS)
		(*dst)->type = INPUT;
	else if ((*current)->type == GREAT)
		(*dst)->type = OUTPUT;
	else if ((*current)->type == DGREAT)
		(*dst)->type = APPEND;
	else
		(*dst)->type = HERE;
	if((*current)->arg[0] == '>')
		(*dst)->newfd = 1;
	if ((*current)->next && (*current)->next->type == WORD)
	{
		(*current) = ((*current)->next);
		(*dst)->word = ft_strdup((*current)->arg);
		if (!(*dst)->word)
		{
			free((*dst)->word);
			free(*dst);
			return(FATAL);
		}
	}
	else
		return (KO);
	if ((*dst)->type == HERE && ft_heredoc(env, *dst) != OK)
	{
		free((*dst)->word);
		free(*dst);
		return (KO);
	}
	return (OK);
}

t_command parsing(t_token_list **current, t_token_type expected, t_env *env)
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
			tree = parse_simple(current, env);
		else if (!operator && (*current)->type == LPARENTHESIS)
			tree = parse_grouping(current, env);
		else if (operator && (*current)->type == PIPE)
			tree = parse_pipe(current, tree, env);
		else if (operator && ((*current)->type == OR_IF || (*current)->type == AND_IF))
			tree = parse_list(current, tree, env);
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
			"word",
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
	*tree = parsing(&current, END, env);
	if (tree->type == PARSE_FATAL)
		return (FATAL);
	else if (g_int)
		return (KO);
	else if (tree->type == PARSE_ERROR)
		return (my_perror(env, (char *[2]){"Syntax error near unexpected token: ",
   (char *)get_token_str(current->type)}, false, KO));
	return (OK);
}
