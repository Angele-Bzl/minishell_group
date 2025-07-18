#include "minishell.h"

void	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("Error: pwd", STDERR_FILENO);
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	return ;
}
