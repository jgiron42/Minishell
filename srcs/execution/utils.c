//
// Created by joachim on 22/02/2022.
//

#include "minishell.h"

t_status	get_g_err(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		return (FATAL);
	if (WIFEXITED(status))
 		g_err = WEXITSTATUS(status);
	else
		g_err = WTERMSIG(status);
	return (OK);
}