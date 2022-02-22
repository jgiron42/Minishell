#include "parsing.h"
#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

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

char			*ft_itoa(int n)
{
	char	*str;
	size_t	j;

	if (n == -2147483648)
	{
		str = ft_strndup(12, "-2147483648\0");
		return (str);
	}
	j = size_int(n);
	if (!(str = (char *)malloc(sizeof(char) * (j + 2))))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str = write_n(str, n, j);
	str[j + 1] = '\0';
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

int	ft_atoi(char *str)
{
	int		negatif;
	int		i;
	int		nb;

	negatif = 0;
	i = 0;
	nb = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		negatif = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10;
		nb = nb + str[i] - '0';
		i++;
	}
	if (negatif == 1)
		return (-nb);
	return (nb);
}
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = (void *)malloc(count * size);
	if (!(s))
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}

/// modifier pour minichoux

void	ft_lstadd_back(t_token_list **alst, t_token_list *new)
{
	t_token_list	*tmp;

	if (!(*alst))
	{
		(*alst) = new;
		new->next = NULL;
	}
	else if (new)
	{
		tmp = (*alst);
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->next = NULL;
	}
}

char	*ft_strndup(size_t n, const char *s1)
{
	size_t		i;
	int		len;
	char	*cpy;

	i = 0;
	len = ft_strlen(s1);
	cpy = (char *)malloc(sizeof(*cpy) * (len + 1));
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	// printf("s1:%s, s2 : %s\n", s1,s2);
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n)
		i++;
	if (i >= n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
