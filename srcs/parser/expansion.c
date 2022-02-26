#include "minishell.h"

char	*ft_strreplace(char *s, char *to_add, size_t start_add, size_t to_pass)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(*ret) * (ft_strlen(new) + ft_strlen(s)
		- (to_pass - start_add) + 1);
	if (!(ret))
		return (NULL);
	while (i < start && s[i])
		ret[i] = s[i++];
	while (to_add[j])
		ret[i + j] = new[j++];
	j = i + j;
	while (s[to_pass])
	{
		ret[j] = s[to_pass];
		to_pass++;
		j++;
	}
	free(s);
	ret[j] = '\0';
	return (ret);
}

int	isvalid_name_letter(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
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
		if (str[i] && !ft_isdigit(str[j]))
		{
			while (str[j] && isvalid_name_letter(str[j]))
				j++;
			key = ft_strndup(j - i , (const char *)(str + i + 1);
			if (!key)
				return (NULL);
			new = get_env_val(env->vars, char *key);
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

t_status	expand_simple(t_simple *command, t_env *env)
{
	t_status ret;

	// pour < a sans arg return KO
	if (!command || !command->argv)
		return(KO);
	while (command->argv && command->argv->arg)
	{
		if (ft_strchr(command->word, '$'))
		{
			command->argv->arg = expand_word(command->argv->arg, env);
			if (!command->argv->arg)
				return (FATAL);
		}
		command->argv = command->argv->next;
	}
	// ft_fillargv_array
	if (command->redir_list)
	{
		ret = expand_redir(command->redir_list, env);
		if (ret != OK)
			return (ret);
	}
	return (OK);
}
