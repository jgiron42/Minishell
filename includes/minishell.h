
#ifndef MINISHELL_H
# define MINISHELL_H

#define NAME minishell


typedef struct s_redirections
{
    struct s_redirections   *next;
    int                     src;
    int                     dst;
}               t_redirections;

typedef struct s_pipeline
{
    struct s_pipeline   *next;
    t_redirections      *redir;
    char                **argv;
}               t_pipeline;

typedef enum    e_separator {AND, OR, SEMI}     t_separator;

typedef struct s_node{
  struct s_node *right;
  struct s_node *left;
  t_separator   sep;
  t_pipeline    *p;
}              t_node;


typedef struct s_env
{
    char            *key;
    char            *value;
    bool            is_exported;
    struct s_env    *next;
}               t_env;

enum ERROR { OK, KO, SYSCALL_FAILURE};

int 	remove_env(t_env **	env, char *key);
int		set_env(t_env **env, char *key, char *value);
char	*get_env(t_env *env, char *key);
int		add_env(t_env **env, char *key, char *value);


#endif
