
#ifndef MINISHELL_H
# define MINISHELL_H

#define NAME minishell
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/stat.h>


typedef struct s_pipeline
{
    struct s_pipeline   *next;
	int           in;
	int           out;
    char                **argv;
}               t_pipeline;

typedef enum    e_separator {AND, OR, SEMI}     t_separator;

typedef struct s_node {
  struct s_node *next;
  struct s_node *sublist;
  bool			is_in_subshell;
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

typedef enum e_status { OK, KO, SYSCALL_FAILURE} t_status;

int 	remove_env(t_env **	env, char *key);
t_status		set_env(t_env **env, char *key, char *value, bool is_exported);
char	*get_env(t_env *env, char *key);
int		add_env(t_env **env, char *key, char *value, bool is_exported); // use in specific case, prefer set_env()
char	**serialize_env(t_env *env);
t_env	*parse_env(char **envp);
void	free_env(t_env *env);
t_env	*dupenv(t_env *src);
bool	path_has_dot(char *path);



#endif
