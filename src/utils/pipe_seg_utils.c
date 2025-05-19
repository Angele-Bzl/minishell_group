# include "minishell.h"

int	skip_quote(const char *str, int *i)
{
	if (str[*i] == '\"') // chercher le second double quote
	{
		*i = *i + 1;
		while (str[*i] != '\"')
		{
			*i = *i + 1;
		}
		return (*i + 1);
	}
	else if (str[*i] == '\'') // chercher le second simple quote
	{
		*i = *i + 1;
		while (str[*i] != '\'')
		{
			*i = *i + 1;
		}
		return (*i + 1);
	}
	if (str[*i] == '\0')
		return (-1);
	return (*i + 1);
}
