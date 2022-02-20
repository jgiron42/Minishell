#include "parsing.h"

// () / {} pour grouping

t_token_type	c_type(t_quote nb, char *str, size_t *len)
{
	int				i;
	const char		*operator[] = {"<<", ">>", "&&", "||",
		">", "<", "|", "(", ")"};
	const t_token_type	type[] = {DLESS, DGREAT, AND_IF, OR_IF, GREAT, LESS,
		PIPE, LPARENTHESIS, RPARENTHESIS, WORD, INVALID};

	i = 0;
	while (i < 9 && ft_strncmp((const char *)str + (*len), operator[i], ft_strlen(operator[i])))
			i++;
	if (i < 9)
		(*len) += !!operator[i][1];
	else if (!nb && ft_isspace(str[*len]))
		return (INVALID);
	else
		return (WORD);
	return (type[i]);
}


size_t	create_t_token_list(char *str, t_token_list **line)
{
	size_t	len;
	t_token_list	*node;
	size_t	tmp;

	len = 0;
	tmp = len;
	node = NULL;
	node = ft_lstnew(c_type(NONE, str, &tmp));
	while (str[len] && WORD == c_type(node->nb, str, &len))
	{
		if (str[len] == '\'')
		{
			if (node->nb == SIMPLE)
				node->nb = NONE;
			else
				node->nb = SIMPLE;
		}
		else if (str[len] == '"')
		{
			if (node->nb == DOUBLE)
				node->nb = NONE;
			else
				node->nb = DOUBLE;
		}
		len++;
	}
	if (len == tmp)
		len++;
	if (!str[len] && node->nb)
	{
		printf("\033[0;31merreur syntax: missing closing quote\n");
		exit(1);
	}
	node->arg = ft_strndup(len, str);
	if (!node->arg)
		exit(2);
	if (node->type != INVALID)
		ft_lstadd_back(line, node);
	return (len);
}

int	main(int argc, char **argv)
{
	t_token_list	*line;
	size_t	i;

	(void)argc;
	i = 0;
	line = NULL;
	while (i < ft_strlen(argv[1]))
	{
		i += create_t_token_list(argv[1] + i, &line);
		if (line)
		{
			printf("La string || %s ||\n type de token : %s\n nb de quote :%s\n", line->arg, ft_itoa(line->type), ft_itoa(line->nb));
			line = line->next;
		}
	}
	return (0);
}
