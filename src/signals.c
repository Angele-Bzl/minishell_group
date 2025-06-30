#include "minishell.h"

static void	ignore_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	quit_lastprompt_init_newprompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// static void	init_newprompt(int signal)
// {
// 	(void)signal;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// }

static void	init_newprompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	set_signals_exec(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &init_newprompt;
	sigaction(SIGINT, &sa, NULL);
	// sa.sa_handler = &sig_quit_init_newprompt;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signals_prompt(void)
{
	struct sigaction	sa;

	ignore_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &quit_lastprompt_init_newprompt;
	sigaction(SIGINT, &sa, NULL);
}

void	set_signals_child(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}