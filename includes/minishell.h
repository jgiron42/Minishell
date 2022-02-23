#ifndef MINISHELL_H
# define MINISHELL_H

#define NAME minishell
#include <stddef.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../srcs/libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../srcs/containers/containers.h"
#include "parsing.h"

typedef struct s_var_list
{
	char            *key;
	char            *value;
	bool            is_exported;
	struct s_var_list    *next;
}               t_var_list;

enum e_redir {INPUT, OUTPUT, APPEND, HERE, DUPIN, DUPOUT, RW};

typedef struct	s_redir {
	enum	e_redir type;	//Lara
	char	*word;	//Lara
	int		newfd; // output:1, input: 0, append: 1, here: 0
	int		oldfd;
	int		fd_save;
	struct	s_redir *next; // ls a c > b  > d
}				t_redir;

typedef struct	s_simple {
	t_redir		*redir_list; //Lara
	t_token_list *argv;		//Lara
	t_var_list	*renv;
	t_var_list	**wenv;
}				t_simple;

typedef struct	s_grouping
{
	struct s_command	*command;
	t_redir				*redir_list;
	bool				is_in_subshell;
}				t_grouping;

union	u_command {
	struct s_simple		simple;
	struct s_pipeline	*pipeline;
	struct s_list		*list;
	struct s_grouping	grouping;
};

enum	e_command_type {SIMPLE, PIPELINE, LIST, GROUPING};

typedef struct s_command {
	enum e_command_type type;
	union u_command		command;
}				t_command;

typedef struct s_pipeline
{
	struct s_pipeline   *next;
	struct s_command	command;
}               t_pipeline;

//utilisation de AND_IF OR_IF et SEMI

typedef struct s_list
{
	struct s_list		*next;
	struct s_pipeline	*pipeline;
	t_token_type		sep;
}               t_list;

typedef struct s_node {
  struct s_node *next;
  struct s_node *sublist;
  bool			is_in_subshell;
  t_token_type   sep;
  t_pipeline    *p;
}              t_node;
//
// typedef struct	s_env {
// 	t_var_list	*vars;
// 	t_bool_vec	opened_files;
// }				t_env;

typedef enum e_status { OK, KO, FATAL} t_status;

typedef char	t_builtin(char **, t_var_list *, t_var_list **);

extern char		g_err;


// env manip:
int 		remove_env(t_var_list **	env, char *key);
int			add_env(t_var_list **env, char *key, char *value, bool is_exported); // use in specific case, prefer set_env()
t_status	set_env(t_var_list **env, char *key, char *value, bool is_exported);
t_status	export_env(t_var_list *env, char *key);
char		*get_env_val(t_var_list *env, char *key);
t_var_list		*get_env_ptr(t_var_list *env, char *key);
void		free_env(t_var_list *env);
t_var_list		*dupenv(t_var_list *src);
// env conversion:
char		**serialize_env(t_var_list *env);
t_status	parse_env(char **envp, t_var_list **env);
//env initialisation:
t_status	init_env(t_var_list **env);
// path_utils:
bool		path_has_dot(char *path);
char 		*ft_realpath(const char *path, char *resolved_path);
// utils
char		*my_get_working_directory(const char *for_whom);
// exec
// t_status	exec_command(t_command cmd, t_env *env);
t_status	perform_assignments(t_var_list **env, t_simple cmd, bool export); // Lara
t_builtin	*is_special_built_in(char *name);
t_builtin	*is_built_in(char *name);

//parsing :
t_command	*parsing(t_token_list **current, t_token_type expected);
void		ft_lstadd_back_redir(t_redir **alst, t_redir *new);

#endif
