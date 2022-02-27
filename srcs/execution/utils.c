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
		g_err = 128 + WTERMSIG(status);
	return (OK);
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

t_status	set_signal(int sig, sighandler_t action, t_env *env)
{
	sighandler_t	ret;

	ret = signal(sig, action);
	if (ret == (sighandler_t)-1)
		return (KO);
	if (env->default_signals[sig] == (sighandler_t)-1)
		env->default_signals[sig] = ret;
	return (OK);
}

void		reset_signals(t_env *env)
{
	if (env->default_signals[SIGINT] != (sighandler_t)-1)
		signal(SIGINT, env->default_signals[SIGINT]);
	if (env->default_signals[SIGQUIT] != (sighandler_t)-1)
		signal(SIGQUIT, env->default_signals[SIGQUIT]);
}