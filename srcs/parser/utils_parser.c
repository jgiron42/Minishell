/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 00:51:43 by ereali            #+#    #+#             */
/*   Updated: 2022/03/03 06:10:31 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isvalid_name_letter(char c)
{
	if (c == '_' || (ft_isalnum(c) && c != '\'' && c != '\\' && c != '\"'))
		return (1);
	return (0);
}

t_status ft_heredoc(t_env *env, t_redir *redir)
{
	char	*rl;
	int		fd;
	bool	quote;
	char	*word;

	quote = false;
	if (ft_strchr(redir->word, '\'') || ft_strchr(redir->word, '\"'))
	{
		quote = true;
		redir->word = remove_quotes(redir->word);
	}
	word = redir->word;
	if (my_tmp_file(&fd, &redir->word) == KO)
		return (KO);
	rl = my_readline(env, "PS2");
	while (ft_strcmp(word, rl))
	{
		if (quote == false)
			rl = expand_word_all(rl, env);
		if (rl)
			write(fd, rl, ft_strlen(rl));
		write(fd, "\n", 1);
		free(rl);
		rl = my_readline(env, "PS2");
	}
	free(rl);
	free(word);
	if(close(fd) != 0)
		return(KO);
	if (fd < 0)
		return (KO);
	redir->oldfd = fd;
	return (OK);
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
	if (!str)
		return (ft_strdup(""));
	if (!inibit)
		return (str);
	new = ft_calloc(sizeof(char) , ft_strlen(str) +
		ft_countoccur(str, inibit) + 1);
	if (!new)
		return (NULL);
	while(str[i])
	{
		if (ft_strchr(inibit, str[i]))
		{
			new[i + j++] = '\\';
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
