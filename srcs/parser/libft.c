#include "parsing.h"
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

int ft_isspace(char c)
{
	if ((c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c == '\r' || c == ' '))
		return (1);
	return (0);
}

static size_t	size_int(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char		*write_n(char *str, int n, size_t i)
{
	while (n > 9)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	str[i] = n + '0';
	return (str);
}


// void	ft_putnbr_fd(int n, int fd)
// {
// 	if (n == -2147483648)
// 	{
// 		ft_putchar_fd('-', fd);
// 		ft_putchar_fd('2', fd);
// 		n = 147483648;
// 	}
// 	if (n < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		n = -n;
// 	}
// 	if (n > 9)
// 		ft_putnbr_fd(n / 10, fd);
// 	ft_putchar_fd('0' + n % 10, fd);
// }

char	*ft_strndup(size_t n, const char *s1)
{
	size_t		i;
	char	*cpy;

	i = 0;
	cpy = (char *)malloc(sizeof(*cpy) * (n + 1));
	if (!(cpy))
		return (NULL);
	while (s1[i] && i < n)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
