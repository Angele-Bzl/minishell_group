#include "../../header/minishell.h"

int	skip_under_quote(const char *str, size_t i)
{
	if (str[i] == '\"') // chercher le second double quote
	{
		while (str[i] != '\"')
		{
			i++;
		}
	}
	else if (str[i] == '\'') // chercher le second simple quote
	{
		while (str[i] != '\'')
		{
			i++;
		}
	}
	if (str[i] == '\"' || str[i] == '\'')
		return (i);
	else
	{
		// syntax error. on ne gere pas les unclosed quote
	}
	return (0);
}
