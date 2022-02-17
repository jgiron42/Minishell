#include "mini.h"

// char *keys[] = { "<", "<<",
// t_token values[] = {LESS, GREAT, PIPE}
// size_t i;

t_token	c_type(t_quote nb, char *str, size_t *len)
{
	t_token type;

	if (!nb && str[*len] == '<')
	{
		if (str[*len + 1] == '<')
		{
			type = DLESS;
			(*len)++;
		}
		else
			type = LESS;
	}
	else if (!nb && str[*len] == '>')
	{
		if (str[*len + 1] == '>')
		{
			type = DGREAT;
			(*len)++;
		}
		else
			type = GREAT;
	}
	else if (!nb && str[*len] == '|')
	{
		if (str[*len + 1] == '|')
		{
			type = OR_IF;
			(*len)++;
		}
		else
			type = PIPE;
	}
	else if (!nb && str[*len] == '&' && str[*len + 1] == '&')
	{
		type = AND_IF;
		(*len)++;
	}
	else if (ft_isspace(str[*len]))
	{
		if (nb)
			type = WORD;
		else
			type = INVALID;
	}
	else
		type = WORD;
	return (type);
}

size_t	create_t_arg(char *str, t_arg **line)
{
	size_t	len;
	t_arg	*node;

	len = 0;
	node = NULL;
	node = ft_lstnew(c_type(NONE, str, &len));
	while (str[len] && node->type == c_type(node->nb, str, &len))
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
	if (!str[len] && node->nb)
	{
		printf("\033[0;31merreur syntax: missing closing quote\n");
		exit(1);
	}
	node->arg = ft_strndup(len + 1, str);
	if (!node->arg)
		exit(2);
	ft_lstadd_back(line, node);
	return (len);
}

int	main(int argc, char **argv)
{
	t_arg	*line;
	size_t	i;
	//
	(void)argc;
	(void)**argv;

	i = 0;
	line = NULL;
	while (i < ft_strlen(argv[1]))
	{
		i += create_t_arg(argv[1] + i, &line);
		printf("La string || %s ||\n type de token : %s\n nb de quote :%s\n", line->arg, ft_itoa(line->type), ft_itoa(line->nb));
		line = line->next;
	}
	return (0);
}
