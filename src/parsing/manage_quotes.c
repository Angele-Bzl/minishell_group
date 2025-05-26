# include "minishell.h"

int		manage_quotes(char c, t_parsing *parsing)  // Pour l'expand
{
	if (c == '\'')
	{
		if (parsing->double_quote == true) // on se trouve deja dans une double quote
			return (ALL_OK);
		if (parsing->simple_quote == true) // si on est deja dans la quote
			parsing->simple_quote = false; // on sort
		else if (parsing->simple_quote == false) // si on est pas dans la quote
			parsing->simple_quote = true; // on rentre
		return (ALL_OK);
	}
	else if (c == '\"')
	{
		if (parsing->simple_quote == true) // on se trouve deja dans une double quote
			return (ALL_OK);
		if (parsing->double_quote == true) // si on est deja dans la quote
			parsing->double_quote = false; // on sort
		else if (parsing->double_quote == false) // si on est pas dans la quote
			parsing->double_quote = true; // on rentre
		return (ALL_OK);
	}
	return (ALL_OK);
}
