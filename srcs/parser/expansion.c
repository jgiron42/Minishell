#include "minishell.h"

// int	*ft_tabzero(int tab[3])
// {
// 	int 	tab[3];
//
// 	i = 0;
//
// 	return (tab);
// }

// pour plus modulable tableau propre
bool	need_to_expand(char *str, size_t dollard)
{
	size_t	i;
	int		j;
	int 	tab[3];

	i = 0;
	// tab = ft_tabzero(tab);
	j=0;
	while (j < 3)
	{
		tab[j] = 0;
		j++;
	}
	while (i < dollard)
	{
		if (str[i] == '\'' && !tab[1] && !tab[2])
		{
			if (tab[0] == 0)
				tab[0] = 1;
			else
				tab[0] = 0;
		}
		else if (str[i] == '\"' && !tab[0] && !tab[2])
		{
			if (tab[1] == 0)
				tab[1] = 1;
			else
				tab[1] = 0;
		}
		else if (str[i] == '\\' && !tab[0] && !tab[2])
		{
			if (tab[2] == 0)
				tab[2] = 1;
			else
				tab[2] = 0;
		}
		i++;
	}
	if (tab[0] || tab[2])
		return (false);
	return (true);
}

char	*expand_word(char *str, t_env *env)
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
		if (str[i] && !ft_isdigit(str[j]) && need_to_expand(str, i))
		{
			while (str[j] && isvalid_name_letter(str[j]))
				j++;
			key = ft_strndup(j - i , (const char *)(str + i + 1));
			if (!key)
				return (NULL);
			new = get_var_val(env, key);
			if (!new)
				return (NULL);
			str = ft_strreplace(str, new, i, i + ft_strlen(key) + 1);
			if (!str)
				return (NULL);
		}
		else if (str[i])
			i++;
	}
	return (new);
}

t_status	expand_redir(t_redir *command, t_env *env)
{
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
		command = command->next;
	}
	if (!command)
		return (OK);
	return (KO);
}

t_status	ft_fillargv(t_simple *command)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_lstsize(command->argv_tokens) + 1));
	if (!tab)
		return (FATAL);
	while (command && command->argv_tokens)
	{
		tab[i] = command->argv_tokens->arg;
		i++;
		command->argv_tokens = command->argv_tokens->next;
	}
	tab[i] = NULL;
	command->argv = tab;
	return (OK);
}

t_status	expand_simple(t_simple *command, t_env *env)
{
	t_status ret;
	t_token_list *beggin;

	// pour < a sans arg return KO
	beggin = command->argv_tokens;
	if (!command || !command->argv_tokens)
		return(KO);
	while (command->argv_tokens && command->argv_tokens->arg)
	{
		if (ft_strchr(command->argv_tokens->arg, '$'))
		{
			command->argv_tokens->arg = expand_word(command->argv_tokens->arg, env);
			if (!command->argv_tokens->arg)
				return (FATAL);
		}
		command->argv_tokens = command->argv_tokens->next;
	}
	command->argv_tokens = beggin;
	ft_fillargv(command);
	command->argv_tokens = beggin;
	if (command->redir_list)
	{
		ret = expand_redir(command->redir_list, env);
		if (ret != OK)
			return (ret);
	}
	return (OK);
}
