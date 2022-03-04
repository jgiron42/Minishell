//
// Created by joachim on 27/02/2022.
//

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_err = 128 + SIGSEGV;
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

void	reset_signals(t_env *env)
{
	if (env->default_signals[SIGINT] != (sighandler_t)-1)
		signal(SIGINT, env->default_signals[SIGINT]);
	if (env->default_signals[SIGQUIT] != (sighandler_t)-1)
		signal(SIGQUIT, env->default_signals[SIGQUIT]);
}
