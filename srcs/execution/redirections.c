
#include "minishell.h"

t_status	redir(int oldfd, int newfd, int *save, t_env *env)
{
	*save = dup (newfd);
	if (env->opened_files.size >= *save)
		bool_vec_resize(&env->opened_files, env->opened_files.size + 1, false);
	env->opened_files.data[*save] = true;
	if (*save == -1 || dup2(oldfd, newfd) == -1)
		return (FATAL);
	env->opened_files.data[oldfd] = false;
	close(oldfd);
}

t_status	open_redir(t_env *env, t_redir *r)
{
	int new_fd;

	if (r->type == OUTPUT) // >
		new_fd = open(r->word, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	else if (r->type == APPEND) // >>
		new_fd = open(r->word, O_CREAT | O_WRONLY | O_APPEND, 00644);
	else if (r->type == INPUT) // <
		new_fd = open(r->word, O_RDONLY);
	else // (r->type == RW)  <>
		new_fd = open(r->word, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (new_fd == -1)
		return (FATAL);
	if (new_fd >= env->opened_files.size)
		bool_vec_resize(&env->opened_files, env->opened_files.size + 1, false);
	env->opened_files.data[new_fd] = true;
	r->oldfd = new_fd;
	return (OK);
}

t_status perform_redirection(t_env *env, t_redir *list)
{
	while (list)
	{
		if (list->type != HERE && list->type != DUPIN && list->type != DUPOUT &&
			open_redir(env, list) == FATAL)
			return (FATAL);
		redir(list->oldfd, list->newfd, &list->fd_save, env);
		list = list->next;
	}
}

t_status reset_redirection(t_env *env, t_redir *list);
