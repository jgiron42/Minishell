#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef enum	e_token_type {INVALID, WORD = 1, GREAT = 2, LESS = 4, DLESS = 8, DGREAT = 16, PIPE = 32, AND_IF = 64, OR_IF = 128, LPARENTHESIS = 256, RPARENTHESIS = 512, SEMI = 1024, END = 2048}	t_token_type;
							// 0		1		2	3		4		5	6		7		8		9			10				11
typedef enum	e_quote {NONE, ONE, DOUBLE}	t_quote;

typedef struct s_token_list
{
	char*				arg;
	t_token_type		type;
	t_quote				nb;
	struct s_token_list	*next;
}				t_token_list;

size_t			ft_strlen(const char *s);
int				ft_isspace(char c);
int				ft_atoi(char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
t_token_list	*ft_lstnew(t_token_type token);
void			ft_lstadd_back(t_token_list **alst, t_token_list *new);
void			ft_putnbr_fd(int n, int fd);
char			*ft_itoa(int n);
char			*ft_strndup(size_t n, const char *s1);

#endif
