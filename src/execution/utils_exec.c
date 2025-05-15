# include "minishell.h"

char	*ft_strtrim_improved(char *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*result;

	i = 0;
	start = -1;
	end = -2;
	while (s1[i] && start == -1)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			start = i;
		i++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0 && end == -2)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			end = i;
		i--;
	}
	result = ft_substr(s1, start, (end - start) + 1);
	free(s1);
	return (result);
}

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
int	tablen(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}