#include "minishell.h"
#include <readline/readline.h>
#include <sys/wait.h>
#include <signal.h>

static void	ignore_sigquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	exec_handler(int signal)
{
	if (signal == SIGINT)
		write(1, "\n", 1);
	if (signal == SIGQUIT)
		write(1, "Quit (core dumped)\n", 20);
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	prompt_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_on(t_mode mode)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	if (mode == PROMPT_MODE)
	{
		ignore_sigquit();
		sa.sa_handler = &prompt_handler;
		sigaction(SIGINT, &sa, NULL);
	}
	if (mode == EXEC_MODE)
	{
		sa.sa_handler = &exec_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (mode == HEREDOC_MODE)
	{
		ignore_sigquit();
		sa.sa_handler = &heredoc_handler;
		sigaction(SIGINT, &sa, NULL);
	}
}
