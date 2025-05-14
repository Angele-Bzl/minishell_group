#include "../header/minishell.h"

int	main(int argc, char **argv)
{
	(void)argc;
	int	i;
	char **prompt_tab;

	i = 0;
	prompt_tab = split_pipe_smart(argv[1], '|');
	while (prompt_tab[i])
	{
		printf("%s\n", prompt_tab[i]);
		i++;
	}
	return (0);
}