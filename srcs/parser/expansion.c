/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:12:29 by ereali            #+#    #+#             */
/*   Updated: 2022/03/04 21:20:44 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_word_all(char *str, t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
		i++;
		j = i + 1;
		if (str[i] && str[j] && !ft_isdigit(str[j]))
		{
			while (str[j] && isvalid_name_letter(str[j]) == true)
				j++;
			if (str[j] == '?' && j == i + 1)
				j++;
			str = ft_replacekey(i, j, str, env);
			if (!str)
				return (NULL);
		}
		else if (str[i])
		i++;
	}
	return (str);
}

char	*expand_word(char *str, t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		j = i + 1;
		if (str[i] && str[j] && !ft_isdigit(str[j])
			&& need_to_expand(str, i) < 2)
		{
			while (str[j] && isvalid_name_letter(str[j]) == true)
				j++;
			if (str[j] == '?' && j == i + 1)
				j++;
			str = ft_replacekey(i, j, str, env);
			if (!str)
				return (NULL);
		}
		else if (str[i])
			i++;
	}
	return (str);
}

t_status	expand_redir(t_redir **first, t_env *env)
{
	t_redir	*command;

	command = (*first);
	if (!command)
		return (KO);
	while (command && command->word)
	{
		if (ft_strchr(command->word, '$'))
		{
			command->word = expand_word(command->word, env);
			if (!command->word)
				return (FATAL);
		}
		command->word = remove_quotes(command->word);
		command = command->next;
	}
	if (!command)
		return (OK);
	return (KO);
}

void		free_vec(t_str_vec *v)
{
	while (--v->size >= 0)
		free(v->data[v->size]);
	free(v->data);
	v->data = NULL;
}

t_status	expand_path(t_token_list *lst, t_str_vec *dst)
{
	int	tmp;
	char *tmp_s;

	*dst = str_vec_init();
	while (lst)
	{
		tmp = dst->size;
		if (lst->arg[0] && path_match_current(lst->arg, dst) == FATAL)
			return (free_vec(dst), FATAL);
		if (tmp == dst->size)
		{
			tmp_s = ft_strdup(lst->arg);
			if (!tmp_s || str_vec_push(dst, tmp_s) == FATAL)
				return (free_vec(dst), FATAL);
		}
		lst = lst->next;
	}
	if (str_vec_push(dst, NULL) == FATAL)
		return (free_vec(dst), FATAL);
	return (OK);
}

t_status	ft_fillargv(t_simple *command)
{
	int			i;
	int			j;
	t_str_vec	dst;

	i = 0;
	j = 0;
	if (!command->argv_tokens)
		return (OK);
	if (expand_path(command->argv_tokens, &dst) == FATAL)
		return (FATAL);
	while (j < dst.size - 1)
	{
		if (dst.data[j][0])
		{
			dst.data[i] = remove_quotes(dst.data[j]);
			i++;
		}
		j++;
	}
	dst.data[i] = NULL;
	command->argv = dst.data;
	return (OK);
}

// pour < a sans arg return KO
t_status	expand_simple(t_simple *command, t_env *env)
{
	t_status ret;
	t_token_list *begin;

	if (!command || !command->argv_tokens)
		return(KO);
	begin = command->argv_tokens;
	while (command->argv_tokens && command->argv_tokens->arg)
	{
		command->argv_tokens->arg = expand_word(command->argv_tokens->arg, env);
		if (!command->argv_tokens->arg)
			return (FATAL);;
		if (ft_field_split(&command->argv_tokens) != OK)
			return (FATAL);
		command->argv_tokens = command->argv_tokens->next;
	}
	command->argv_tokens = begin;
	ft_fillargv(command);
	if (command->redir_list)
	{
		ret = expand_redir(&command->redir_list, env);
		if (ret != OK)
			return (ret);
	}
	return (OK);
}
