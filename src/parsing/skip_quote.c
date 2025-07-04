#include "minishell.h"

int	skip_quote(const char *str, int *i)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		while (str[*i] != '\"')
		{
			*i = *i + 1;
		}
		return (*i + 1);
	}
	else if (str[*i] == '\'')
	{
		*i = *i + 1;
		while (str[*i] != '\'')
		{
			*i = *i + 1;
		}
		return (*i + 1);
	}
	return (*i + 1);
}
