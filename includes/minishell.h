
#ifndef MINISHELL_H
# define MINISHELL_H

#define NAME minishell
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include "../srcs/libft/libft.h"


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

typedef enum e_status { OK, KO, FATAL} t_status;

extern char		g_err;


// env manip:
int 		remove_env(t_env **	env, char *key);
int			add_env(t_env **env, char *key, char *value, bool is_exported); // use in specific case, prefer set_env()
t_status	set_env(t_env **env, char *key, char *value, bool is_exported);
t_status	export_env(t_env *env, char *key);
char		*get_env_val(t_env *env, char *key);
t_env		*get_env_ptr(t_env *env, char *key);
void		free_env(t_env *env);
t_env		*dupenv(t_env *src);
// env conversion:
char		**serialize_env(t_env *env);
t_status	parse_env(char **envp, t_env **env);
//env initialisation:
t_status	init_env(t_env **env);
// path_utils:
bool		path_has_dot(char *path);
char 		*ft_realpath(const char *path, char *resolved_path);
// utils
char		*my_get_working_directory(const char *for_whom);



#endif
