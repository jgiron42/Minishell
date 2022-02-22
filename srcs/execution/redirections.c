#include "minishell.h"

t_status	redir(int oldfd, int newfd, int *save, t_env *env)
{
	if (save &&	env->opened_files.size > newfd && env->opened_files.data[newfd])
	{
		*save = dup (newfd);
		if (*save == -1)
			return (FATAL);
		if (env->opened_files.size <= *save)
			bool_vec_resize(&env->opened_files, *save, false);
		env->opened_files.data[*save] = true;
	}
	if (dup2(oldfd, newfd) == -1)
		return (FATAL);
	env->opened_files.data[oldfd] = false;
	if (newfd >= env->opened_files.size)
		bool_vec_resize(&env->opened_files, newfd, false);
	env->opened_files.data[newfd] = true;
	close(oldfd);
	return (OK);
}

t_status	open_redir(t_env *env, t_redir *r)
{
	int old_fd;

	if (r->type == OUTPUT)
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
		env->opened_files.data[list->fd_save] = false;
	}
	else
	{
		close(list->newfd);
		env->opened_files.data[list->newfd] = false;
	}
	return (OK);
}