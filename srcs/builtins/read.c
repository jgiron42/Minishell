#include "minishell.h"
/*
static bool	escape(char *str)
{
	bool	is_escaped;
	int		i;
	int		j;

	i = 0;
	j = 0;
	is_escaped = false;
	while(str[i])
	{
		if (str[i] == '\\' && is_escaped)
		{
			str[j] = str[i];
			is_escaped = false;
			++j;
		}
		else if (str[i] == '\\')
			is_escaped = true;
		else
			++j;
		++i;
	}
	str[j] = 0;
	return (is_escaped);
}

static char	assign(char **argv, t_env *env, char *buf)
{
	int	i;
	char *charset;
	char *tmp;

	charset = get_var_val(env, "IFS");
	i = 0;
	while (buf[i])
	{
		if (strchr(charset, buf[i]))
		{
			if (i == 1)
				buf++;
			else {
				tmp = ft_substr(buf, 0, i);
				if (!tmp)
				{
					perror("read");
					return (1);
				}
				if (set_var(env, *argv,  tmp, false) == KO)
					return (1);
				buf += i;
				argv++;
			}
			i = 0;
		}
		++i;
	}
	while (*argv)
	{
		tmp = ft_substr(buf, 0, i);
		if (!tmp)
		{
			perror("read");
			return (1);
		}
		set_var(env, *argv,  tmp, false);
		++argv;
	}
	return (0);
}

char	read_shell(char **argv, t_env *env)
{
	char	*ret;
	char	*ps2;
	char	*buf;
	char	option[256];

	my_getopt(&argv, "r",option);
	while (1)
	{
		ret = readline(ps2);
		if (!ps2)
			ps2 = get_var_val(env, "PS2");
		if (!ret)
			break;
		buf = ft_strjoinff(buf, ret);
		if (!buf)
		{
			perror("read");
			return (1);
		}
		if (option['r'] || !escape(buf))
			break;
	}
	return (assign(argv, env, buf));
}*/