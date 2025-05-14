#include "../../header/minishell.h"

int	skip_under_quote(char *str, int i)
{
	if (str[i] == "\"") // chercher le second double quote
	{
		while (str[i] != "\"")
		{
			i++;
		}
	}
	else if (str[i] == "\'") // chercher le second simple quote
	{
		while (str[i] != "\'")
		{
			i++;
		}
	}
	return (i);
}
