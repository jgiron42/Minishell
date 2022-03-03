/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:12:29 by ereali            #+#    #+#             */
/*   Updated: 2022/03/03 07:18:56 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	need_to_expand(char *str, size_t dollard)
{
	size_t	i;
	int		j;
	int 	tab[3];

	i = 0;
	j = 0;
	while (j < 3)
	{
		tab[j] = 0;
		j++;
	}
	while (i < dollard)
	{
		if (tab[2] == 4)
			tab[2] = 0;
		else if (str[i] == '\"' && !tab[1] && !tab[2])
		{
			if (tab[0] == 0)
				tab[0] = 1;
			else
				tab[0] = 0;
		}
		else if (str[i] == '\'' && !tab[0] && !tab[2])
		{
			if (tab[1] == 0)
				tab[1] = 2;
			else
				tab[1] = 0;
		}
		else if (str[i] == '\\' && !tab[1])
			tab[2] = 4;
		i++;
	}
	return (tab[0] + tab[1] + tab[2]);
}

char	*expand_word_all(char *str, t_env *env)
{
	char	*new;
	char	*key;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		j = i + 1;
		if (str[i] && !ft_isdigit(str[j]))
		{
			while (str[j] && isvalid_name_letter(str[j]) == true)
				j++;
			if (str[j] == '?' && j == i + 1)
				j++;
			key = ft_strndup(j - i - 1, (const char *)(str + i + 1));
			if (!key)
				return (NULL);
			if (!ft_strcmp(key, "?"))
				new = ft_itoa(g_err);
			else
			{
				new = get_var_val(env, key);
				new = ft_inhibit(new, "\\\"\'*");
				if (!new)
					return (NULL);
			}
			str = ft_strreplace(str, new, i, i + ft_strlen(key) + 1);
			if (!str)
				return (NULL);
			else
			{
				free(key);
				free(new);
			}
		}
		else if (str[i])
			i++;
	}
	return (str);
}


char	*expand_word(char *str, t_env *env)
{
	char	*new;
	char	*key;
	size_t	i;
	size_t	j;

	i = 0;
	// key = NULL;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		j = i + 1;
		if (str[i] && !ft_isdigit(str[j]) && need_to_expand(str, i) < 2)
		{
			while (str[j] && isvalid_name_letter(str[j]) == true)
				j++;
			if (str[j] == '?' && j == i + 1)
				j++;
			key = ft_strndup(j - i - 1, (const char *)(str + i + 1));
			if (!key)
				return (NULL);
			if (!ft_strcmp(key, "?"))
				new = ft_itoa(g_err);
			else
			{
				new = get_var_val(env, key);
				new = ft_inhibit(new, "\\\"\'*");
				if (!new)
					return (NULL);
			}
			str = ft_strreplace(str, new, i, i + ft_strlen(key) + 1);
			if (!str)
				return (NULL);
			else
			{
				free(key);
				free(new);
			}
		}
		else if (str[i])
			i++;
	}
	return (str);
}

t_status	expand_redir(t_redir **first, t_env *env)
{
	t_redir *command;

	command = (*first);
	if (!command)
		return(KO);
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

// appeler si need to expand arg[i]
t_status	ft_field_split(t_token_list **lst)
{
	char *arg;
	int	i;

	i = ft_strlen((*lst)->arg);
	if (i > 0)
		i -= 1;
	while (i != 0)
	{
		while (i != 0 && !(ft_isspace((*lst)->arg[i]) &&
			need_to_expand((*lst)->arg, i) == 0))
			i--;
		if (i != 0)
		{
			arg = ft_strdup((*lst)->arg + i + 1);
			if (!arg)
				return (FATAL);
			if (ft_strcmp(arg, ""))
				if (ft_lstinsertword(lst, arg) == FATAL)
					return (FATAL);
			(*lst)->arg[i] = '\0';
		}
	}
	return (OK);
}

t_status	expand_path(t_token_list *lst, t_str_vec *dst)
{
	*dst = str_vec_init();
	while (lst)
	{
		if (lst->arg[0] && path_match(lst->arg, dst) == FATAL)
		{
			while (--dst->size >= 0)
				free(dst->data[dst->size]);
			return (FATAL);
		}
		lst = lst->next;
	}
	str_vec_push(dst, NULL);
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
		command->argv_tokens = begin;
	}
	return (OK);
}
