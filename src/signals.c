#include "minishell.h"

int g_sig_state = 0;

void	handle_sigint(int sig)
{
	printf("%d\n", g_sig_state);
	(void)sig;
	if (g_sig_state == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sig_state == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(0); // ferme l'entrée pour forcer readline/heredoc à s'interrompre
	}
	g_sig_state = 1;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_sig_state == 0)
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
}

void	init_signals(void)
{
	struct sigaction	sa;
	
	// sa = NULL;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}