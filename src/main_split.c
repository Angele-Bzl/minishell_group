#include "../header/minishell.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	i;
	char **prompt_tab;
	char *arg;

	arg = "hey | hello | bonjour | hej";
	i = 0;
	prompt_tab = split_pipe_smart(arg, '|');
	while (prompt_tab[i])
	{
		printf("%s\n", prompt_tab[i]);
		i++;
	}
	return (0);
}
