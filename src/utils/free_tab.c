# include "minishell.h"

char	*free_tab(char **table)
{
	int	i;

	if (!table)
		return (NULL);
	i = 0;
	if (table && table[i])
	{
		free(table[i]);
		table[i] = NULL;
	}
	i++;
	while (table[i])
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
	return (NULL);
}
