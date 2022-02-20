#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef enum	e_token {INVALID, WORD, GREAT, LESS, DLESS, DGREAT, PIPE, AND_IF, OR_IF, LPARENTHESIS, RPARENTHESIS}	t_token;
						// 0		1		2	3		4		5	6		7		8		9			10
typedef enum	e_quote {NONE, SIMPLE, DOUBLE}	t_quote;

//node
typedef struct s_arg
{
	char*			arg;
	t_token			type;
	t_quote			nb;
	struct s_arg	*next;
}				t_arg;

size_t	ft_strlen(const char *s);
int ft_isspace(char c);
int	ft_atoi(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
t_arg	*ft_lstnew(t_token token);
void	ft_lstadd_back(t_arg **alst, t_arg *new);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
char	*ft_strndup(size_t n, const char *s1);


#endif
