#include "minishell.h"

static void	ignore_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	prompt_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
		printf("sigint\n");
	if (signal == SIGQUIT)
		printf("sigquit\n");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
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

void	set_exec_signals(void)
{
	struct sigaction	sa;

	printf("exec\n");
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &exec_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_prompt_signals(void)
{
	struct sigaction	sa;

	ignore_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &prompt_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	set_default_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	set_default_signals();
	ignore_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
}
