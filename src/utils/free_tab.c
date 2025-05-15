# include "minishell.h"

char	*free_tab(char **table)
{
	int	i;

	i = 0;
	if (table && table[i])
	{
		free(table[i]);
		table[i] = NULL;
	}
	i++;
	while (table && table[i])
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	if (table)
	{
		free(table);
		table = NULL;
	}
	return (NULL);
}
