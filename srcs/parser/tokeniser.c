#include "parsing.h"
#include "minishell.h"

// () / {} pour grouping

t_token_type	c_type(t_quote nb, const char *str, size_t len)
{
	int				i;
	const char		*operator[] = {"<<", ">>", "&&", "||",
		">", "<", "|", "(", ")"};
	const t_token_type	type[] = {DLESS, DGREAT, AND_IF, OR_IF, GREAT, LESS,
		PIPE, LPARENTHESIS, RPARENTHESIS, WORD, INVALID};

	i = 0;
	while (i < 9 && ft_strncmp((const char *)str + (len), operator[i], ft_strlen(operator[i])))
			i++;
	if (i > 8 && !nb && ft_isspace(str[len]))
		return (INVALID);
	else if (i > 8)
		return (WORD);
	return (type[i]);
}


size_t	create_t_token_list(const char *str, t_token_list **line)
{
	size_t	len;
	t_token_list	*node;
	bool	escaped = false;

	len = 0;
	node = NULL;
	node = ft_lstnew(c_type(NONE, str, len));
	while (str[len] && (escaped || WORD == c_type(node->nb, str, len)))
	{
		if (str[len] == '\'' && !escaped)
		{
			if (node->nb == ONE)
				node->nb = NONE;
			else
				node->nb = ONE;
		}
		else if (str[len] == '"' && !escaped)
		{
			if (node->nb == DOUBLE)
				node->nb = NONE;
			else
				node->nb = DOUBLE;
		}
		else if (str[len] == '\\' && node->nb != ONE && !escaped)
			escaped = true;
		else if (escaped)
			escaped = false;
		len++;
	}
	if (node->type != WORD)
		len ++;
	if (node->type == DLESS || node->type == DGREAT || node->type == OR_IF || node->type == AND_IF)
		len++;
	if (!str[len] && node->nb)
	{
		printf("\033[0;31merreur syntax: missing closing quote\n");
		exit(1);
	}
	if (node->type != INVALID)
	{
		node->arg = ft_strndup(len, str);
		if (!node->arg)
			exit(2);
		ft_lstadd_back(line, node);
	}
	return (len);
}

t_token_list	*tokenise(char *str)
{
	t_token_list	*line;
//	t_token_list	*end;
	size_t	i;

	i = 0;
	line = NULL;
	while (i < ft_strlen(str))
		i += create_t_token_list(str + i, &line); //TODO: gestion d'erreurs
//	end = ft_lstnew(END);
//	if (!end)
//		;
//	ft_lstadd_back(&line, end);
//	ft_prin(&line);
	return (line);
}



int	main(int argc, char **argv)
{
	t_token_list	*line;
	t_command		tree;
	size_t	i;

	(void)argc;
	i = 0;
	line = NULL;
	while (i < ft_strlen(argv[1]))
		i += create_t_token_list(argv[1] + i, &line);
	ft_prin(&line);
	tree = parsing(&line, END);
	// if (tree.type == SIMPLE)
	// {
	// 	if (tree.command.simple.argv)
	// 	{
	// 		printf("-----------------argv---------------------\n" );
	// 		ft_prin(&(tree.command.simple.argv));
	// 		printf("---------------END------------\n" );
	// 	}
	// 	// printf("-------redir------------\n");
	// 	// ft_prin_redir(&(tree.command.simple.redir_list));
	// }

	return (0);
}
