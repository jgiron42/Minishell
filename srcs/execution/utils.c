//
// Created by joachim on 22/02/2022.
//

#include "minishell.h"

const char	*signal_messages[NSIG] = {
#ifdef SIGHUP
		[SIGHUP] = "Hangup",
#endif
#ifdef SIGINT
//		[SIGINT] = "Interrupt",
#endif
#ifdef SIGQUIT
		[SIGQUIT] = "Quit",
#endif
#ifdef SIGILL
		[SIGILL] = "Illegal instruction",
#endif
#ifdef SIGTRAP
		[SIGTRAP] = "BPT trace/trap",
#endif
#ifdef SIGABRT
		[SIGABRT] = "ABORT instruction",
#endif
#ifdef SIGEMT
		[SIGEMT] = "EMT instruction",
#endif
#ifdef SIGFPE
		[SIGFPE] = "Floating point exception",
#endif
#ifdef SIGKILL
		[SIGKILL] = "Killed",
#endif
#ifdef SIGBUS
		[SIGBUS] = "Bus error",
#endif
#ifdef SIGSEGV
		[SIGSEGV] = "Segmentation fault",
#endif
#ifdef SIGSYS
		[SIGSYS] = "Bad system call",
#endif
#ifdef SIGPIPE
		[SIGPIPE] = "Broken pipe",
#endif
#ifdef SIGALRM
		[SIGALRM] = "Alarm clock",
#endif
#ifdef SIGTERM
		[SIGTERM] = "Terminated",
#endif
#ifdef SIGURG
		[SIGURG] = "Urgent IO condition",
#endif
#ifdef SIGSTOP
		[SIGSTOP] = "Stopped (signal)",
#endif
#ifdef SIGTSTP
		[SIGTSTP] = "Stopped",
#endif
#ifdef SIGCONT
		[SIGCONT] = "Continue",
#endif
#ifdef SIGCHLD
		[SIGCHLD] = "Child death or stop",
#endif
#ifdef SIGTTIN
		[SIGTTIN] = "Stopped (tty input)",
#endif
#ifdef SIGTTOU
		[SIGTTOU] = "Stopped (tty output)",
#endif
#ifdef SIGIO
		[SIGIO] = "I/O ready",
#endif
#ifdef SIGXCPU
		[SIGXCPU] = "CPU limit",
#endif
#ifdef SIGXFSZ
		[SIGXFSZ] = "File limit",
#endif
#ifdef SIGVTALRM
		[SIGVTALRM] = "Alarm (virtual)",
#endif
#ifdef SIGPROF
		[SIGPROF] = "Alarm (profile)",
#endif
#ifdef SIGWINCH
		[SIGWINCH] = "Window changed",
#endif
#ifdef SIGLOST
		[SIGLOST] = "Record lock",
#endif
#ifdef SIGUSR1
		[SIGUSR1] = "User signal 1",
#endif
#ifdef SIGUSR2
		[SIGUSR2] = "User signal 2",
#endif
#ifdef SIGMSG
		[SIGMSG] = "HFT input data pending",
#endif
#ifdef SIGPWR
		[SIGPWR] = "power failure imminent",
#endif
#ifdef SIGDANGER
		[SIGDANGER] = "system crash imminent",
#endif
#ifdef SIGMIGRATE
		[SIGMIGRATE] = "migrate process to another CPU",
#endif
#ifdef SIGPRE
		[SIGPRE] = "programming error",
#endif
#ifdef SIGGRANT
		[SIGGRANT] = "HFT monitor mode granted",
#endif
#ifdef SIGRETRACT
		[SIGRETRACT] = "HFT monitor mode retracted",
#endif
#ifdef SIGSOUND
		[SIGSOUND] = "HFT sound sequence has completed",
#endif
#ifdef SIGINFO
		[SIGINFO] = "Information request"
#endif
};

t_status	get_g_err(t_env *env, pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		return (FATAL);
	if (WIFEXITED(status))
 		g_err = WEXITSTATUS(status);
	else
	{
		g_err = 128 + WTERMSIG(status);
		if (env->is_interactive)
		{
			ft_putstr_fd((char *) signal_messages[WTERMSIG(status)], 2);
			write(2, "\n", 1);
		}
	}
	return (OK);
}

bool	is_dir(char *path)
{
	struct stat buf;

	if (stat(path, &buf) == 0 && S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}
