#include "minishell.h"

t_status	redir(int oldfd, int newfd, int *save, t_env *env)
{
	if (save)
	{
		*save = dup (newfd);
		if (*save == -1)
			return (FATAL);
		if (env->opened_files.size <= *save)
			char_vec_resize(&env->opened_files, *save, FD_CLOSE);
		env->opened_files.data[*save] = FD_TMP;
	}
	if (dup2(oldfd, newfd) == -1)
		return (FATAL);
	if (oldfd < env->opened_files.size)
		env->opened_files.data[oldfd] = FD_CLOSE;
	if (newfd >= env->opened_files.size)
		char_vec_resize(&env->opened_files, newfd, FD_CLOSE);
	env->opened_files.data[newfd] = FD_OPEN;
	close(oldfd);
	return (OK);
}

t_status	open_redir(t_env *env, t_redir *r)
{
	int old_fd;

	if (r->type == OUTPUT || r->type == CLOBBER)
		old_fd = open(r->word, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	else if (r->type == APPEND)
		old_fd = open(r->word, O_CREAT | O_WRONLY | O_APPEND, 00644);
	else if (r->type == INPUT)
		old_fd = open(r->word, O_RDONLY);
	else // (r->type == RW)
		old_fd = open(r->word, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (old_fd == -1)
		return (FATAL);
	return (redir(old_fd, r->newfd, &r->fd_save, env));
}

t_status perform_redirection(t_env *env, t_redir *list)
{
	while (list)
	{
		if (list->type == HERE || list->type == DUPIN || list->type == DUPOUT &&
		redir(list->oldfd, list->newfd, &list->fd_save, env) == FATAL)
			return (FATAL);
		else if (open_redir(env, list) == FATAL)
			return (FATAL);
		list = list->next;
	}
	return (OK);
}

t_status reset_redirection(t_env *env, t_redir *list) // TODO: iteratize
{
	if (!list)
		return (OK);
	if (reset_redirection(env, list->next) == FATAL)
		return (FATAL);
	if (list->type == DUPIN || list->type == DUPOUT)
	{
		if (redir(list->newfd, list->oldfd, NULL, env) == FATAL)
			return (FATAL);
	}
	else if (list->fd_save != -1) {
		if (dup2(list->fd_save, list->newfd) == FATAL)
			return (FATAL);
		close(list->fd_save);
		env->opened_files.data[list->fd_save] = FD_CLOSE;
	}
	else
	{
		close(list->newfd);
		env->opened_files.data[list->newfd] = FD_CLOSE;
	}
	return (OK);
}