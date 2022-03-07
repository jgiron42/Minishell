/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:09:46 by ereali            #+#    #+#             */
/*   Updated: 2022/03/07 14:37:21 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token_list *ptr)
{
	if (!ptr)
		return ;
	free_token_list(ptr->next);
	free(ptr->arg);
	free(ptr);
}

t_token_type	c_type(t_quote nb, const char *str, size_t len)
{
	int					i;
	const char			*operator[] = {"<<", ">>", "&&", "||",
		">", "<", "|", "(", ")"};
	const t_token_type	type[] = {DLESS, DGREAT, AND_IF, OR_IF, GREAT, LESS,
		PIPE, LPARENTHESIS, RPARENTHESIS, WORD, INVALID};

	i = 0;
	while (i < 9 && ft_strncmp((const char *)str + (len), operator[i],
			ft_strlen(operator[i])))
		i++;
	if (i > 8 && !nb && ft_isspace(str[len]))
		return (INVALID);
	else if (i > 8)
		return (WORD);
	return (type[i]);
}

size_t	create_t_token_list(char **str, t_token_list **line, t_env *env)
{
	size_t			len;
	t_token_list	*node;
	bool			escaped;

	len = 0;
	node = NULL;
	escaped = false;
	node = ft_lstnew(c_type(NONE, *str, len));
	if (!node)
		return (FATAL);
	while ((*str)[len] && (escaped || WORD == c_type(node->nb, *str, len)))
	{
		if (escaped)
			escaped = false;
		else if ((*str)[len] == '\'')
		{
			if (node->nb == ONE)
				node->nb = NONE;
			else if (node->nb == NONE)
				node->nb = ONE;
		}
		else if ((*str)[len] == '"')
		{
			if (node->nb == DOUBLE)
				node->nb = NONE;
			else if (node->nb == NONE)
				node->nb = DOUBLE;
		}
		else if ((*str)[len] == '\\' && node->nb != ONE)
			escaped = true;
		len++;
	}
	if (node->type != WORD)
		len ++;
	if (node->type == DLESS || node->type == DGREAT || node->type == OR_IF
		|| node->type == AND_IF)
		len++;
	if (!(*str)[len] && node->nb)
		return (free(node), my_perror(env, (char *[2]){
				"Syntax error: missing closing quote",
				NULL}, false, KO), KO);
	if (node->type != INVALID)
	{
		node->arg = ft_strndup(len, *str);
		if (!node->arg)
			return (free(node), FATAL);
		return (ft_lstadd_back(line, node), *str += len, OK);
	}
	return (free(node), *str += len, OK);
}

t_status	tokenise(char *str, t_token_list **dst, t_env *env)
{
	size_t			i;
	t_status		ret;
	t_token_list	*tmp;

	i = 0;
	*dst = NULL;
	while (i < ft_strlen(str))
	{
		ret = create_t_token_list(&str, dst, env);
		if (ret != OK)
		{
			free_token_list(*dst);
			return (KO);
		}
	}
	tmp = ft_lstnew(END);
	if (!tmp)
	{
		free_token_list(*dst);
		return (FATAL);
	}
	ft_lstadd_back(dst, tmp);
	return (OK);
}
