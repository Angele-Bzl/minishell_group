#include "minishell.h"

int	ft_isspace(char c)
{
	int	i;

	i = 0;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}
