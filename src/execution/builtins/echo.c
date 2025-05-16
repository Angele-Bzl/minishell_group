//# include "minishell.h"

#include "../../../header/minishell.h"

void	exec_echo(char **cmd)
{
	int	i;

	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	if (!strncmp(cmd[1], "-n", 2)) //put back the ft version !
		i = 2;
	else
		i = 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (strncmp(cmd[1], "-n", 2)) //put back the ft version !
		printf("\n");
}

int main(void)
{
	char *cmd[4] = {"echo", "-n", "world", NULL};

	exec_echo(cmd);
}