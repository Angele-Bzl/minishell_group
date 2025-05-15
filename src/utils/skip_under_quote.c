# include "minishell.h"

int	skip_under_quote(const char *str, int i)
{
	if (str[i] != '\"' && str[i] != '\'')
		return (i);
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
		printf("syntaxe error : (quote not closed)\n");
	}
	return (0);
}
