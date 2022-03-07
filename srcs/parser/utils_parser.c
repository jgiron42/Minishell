/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 00:51:43 by ereali            #+#    #+#             */
/*   Updated: 2022/03/07 16:32:23 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isvalid_name_letter(char c)
{
	if (c == '_' || (ft_isalnum(c) && c != '\'' && c != '\\' && c != '\"'))
		return (1);
	return (0);
}

t_status	ft_heredoc(t_env *env, t_redir *redir)
{
	char	*rl;
	int		fd;
	bool	quote;
	char	*word;

	quote = false;
	if (ft_strchr(redir->word, '\'') || ft_strchr(redir->word, '\"'))
	{
		quote = true;
		if (remove_quotes(redir->word) == FATAL)
			return (FATAL);
	}
	word = redir->word;
	if (my_tmp_file(&fd, &redir->word) == KO)
		return (my_perror(env, (char *[2]){
				"can't create here-document", NULL}, true, KO));
	rl = my_readline(env, "PS2");
	while (rl && !g_int && ft_strcmp(word, rl))
	{
		if (quote == false)
			rl = expand_word_all(rl, env);
		if (rl)
			write(fd, rl, ft_strlen(rl));
		write(fd, "\n", 1);
		free(rl);
		rl = my_readline(env, "PS2");
	}
	if (close(fd) != 0)
		return (free(rl), free(word), KO);
	if (g_int)
		return (free(rl), free(word), unlink(redir->word), KO);
	return (free(rl), free(word), redir->oldfd = fd, OK);
}

t_status remove_quotes(char	*str)
{
	char	*cpy;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	cpy = ft_strdup(str);
	if (!cpy)
		return (FATAL);
	while (cpy[i + j])
	{
		if ((ft_strchr("\\\"", cpy[i + j]) && need_to_expand(cpy, i + j) < 2)
			|| (cpy[i + j] == '\'' && (need_to_expand(cpy, i + j) == 2
					|| need_to_expand(cpy, i + j) == 0)))
<<<<<<< HEAD
			str[i] = cpy[i + ++j];
=======
		{
			j++;
			(str)[i] = cpy[i + j];
		}
>>>>>>> 31cb51202b63088468799bd487dcbcf81d2d35cd
		else
		{
			(str)[i] = cpy[i + j];
			i++;
		}
	}
	(str)[i] = '\0';
	free(cpy);
	return (OK);
}

char	*ft_fill_with_bslash(char *str, char *new, const char *inhibit)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strchr(inhibit, str[i]))
		{
			new[i + j++] = '\\';
			new[i + j] = str[i];
			i++;
		}
		while (!ft_strchr(inhibit, str[i]))
		{
			new[i + j] = str[i];
			i++;
		}
	}
	return (new);
}

char	*ft_inhibit(char *str, const char *inhibit)
{
	char	*new;
//	size_t	i;
//	size_t	j;

//	i = 0;
//	j = 0;
	if (!str)
		return (ft_strdup(""));
	if (!inhibit)
		return (str);
	new = ft_calloc(sizeof(char), ft_strlen(str)
			+ ft_countoccur(str, inhibit) + 1);
	if (!new)
		return (NULL);
	new = ft_fill_with_bslash(str, new, inhibit);
	return (new);
}
