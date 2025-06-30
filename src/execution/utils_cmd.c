#include "minishell.h"

size_t	find_path_in_env(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (ERR);
}

void	fill_tab_null(char **table, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		table[i] = NULL;
		i++;
	}
}
