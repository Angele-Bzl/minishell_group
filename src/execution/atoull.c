#include "minishell.h"

static void	go_to_num(const char *str, int *i, int *minus)
{
	if (str[*i] == '+')
		*i = *i + 1;
	else if (str[*i] == '-')
	{
		*minus = -1;
		*i = *i + 1;
	}
}

unsigned long long	ft_atoull(const char *str, int *minus)
{
	unsigned long long	result;
	int					i;

	i = 0;
	result = 0;
	go_to_num(str, &i, minus);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result);
}
