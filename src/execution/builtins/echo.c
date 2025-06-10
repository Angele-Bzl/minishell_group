#include "minishell.h"

// #include "../../../header/minishell.h"

static void	manage_dash(bool *new_line, bool *dash, char **cmd, int i)
{
	int	j;

	j = 1;
	while (cmd[i][j] == 'n')
		j++;
	if (cmd[i][j] == '\0' && *dash == false)
		*new_line = false;
	else
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		*dash = true;
	}
}

static void	print_arg(char **cmd, int i)
{
	printf("%s", cmd[i]);
	if (cmd[i + 1])
		printf(" ");
}

void	exec_echo(char **cmd)
{
	int		i;
	bool	dash;
	bool	new_line;

	new_line = true;
	dash = false;
	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
			manage_dash(&new_line, &dash, cmd, i);
		else
			print_arg(cmd, i);
		i++;
	}
	if (new_line == true)
		printf("\n");
}

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	char *cmd[5] = {"echo", "-p", "-n", "WORLD", NULL};

// 	exec_echo(cmd, env);
// }