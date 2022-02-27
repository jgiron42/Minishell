#include "minishell.h"

t_token_list	*ft_lstnew(t_token_type	 token)
{
	t_token_list *new;

	if (!(new = (t_token_list *)malloc(sizeof(t_token_list))))
		return (NULL);
	new->arg = NULL;
	new->type = token;
	new->nb = NONE;
	new->next = NULL;
	return (new);
}

t_token_list	*ft_lstcpy(t_token_list	 *current)
{
	t_token_list	 *cpy;

	cpy = ft_lstnew(current->type);
	cpy->arg = (current)->arg;
	return (cpy);
}

size_t	ft_lstsize(t_token_list *lst)
{
	size_t	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	isvalid_name_letter(char c)
{
	if (c == '_' || (ft_isalnum(c) && c != '\'' && c != '\\' && c != '\"'))
		return (1);
	return (0);
}

//libft
size_t	ft_countoccur(char *str, const char *to_count)
{
	size_t	i;
	size_t count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (ft_strchr(to_count, str[i]))
			count++;
		i++;
	}
	// printf("Il y a %zu slash a faire\n", count);
	return (count);
}

char	*remove_quotes(char* str)
{
	char	*cpy;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	cpy = ft_strdup(str);
	while(cpy[i + j])
	{
		// printf("j'en suis a %c de %s need to expand retourne %d\n", cpy[i + j], cpy, need_to_expand(cpy, i + j));
		if ((ft_strchr("\\\"" , cpy[i + j]) && need_to_expand(cpy, i + j) < 2) ||
			(cpy[i + j] == '\'' && (need_to_expand(cpy, i + j) == 2 || need_to_expand(cpy, i + j) == 0)))
		{
			j++;
			str[i] = cpy[i + j];
		}
		else
		{
			str[i] = cpy[i + j];
			i++;
		}
	}
	str[i] = '\0';
	free(cpy);
	return (str);
}

char	*ft_inhibit(char *str, const char *inibit)
{
	char *new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	// printf("j'en suis a %s     %s\n", str, inibit);
	if (!str)
		return (NULL);
	if (!inibit)
		return (str);
	new = ft_calloc(sizeof(char) , ft_strlen(str) +
		ft_countoccur(str, inibit) + 1);
	if (!new)
		return (NULL);
	while(str[i])
	{
		// printf("j'en suis a %c\n", str[i]);
		if (ft_strchr(inibit, str[i]))
		{
			new[i + j] = '\\';
			j++;
			new[i + j] = str[i];
			i++;
		}
		while (!ft_strchr(inibit, str[i]))
		{
			new[i + j] = str[i];
			i++;
		}
	}
	return (new);
}
