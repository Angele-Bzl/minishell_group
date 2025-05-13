#include "../../header/minishell.h"

int    manage_simple_quote(t_data *data, t_parsing *parsing)
{
	if (parsing->double_quote == true) // on se trouve deja dans une double quote
		return ALL_OK;
	if (parsing->simple_quote == true) // si on est deja dans la quote
		parsing->simple_quote = false; // on sort
	else if (parsing->simple_quote == false) // si on est pas dans la quote
		parsing->simple_quote = true; // on rentre
	 if (parsing->dollar == true) // gérer le dollar ?
	 	save_word(word_length, promptline, i, data, booleans);
	return (ALL_OK);
}

int    manage_double_quote(t_data *data, t_parsing *parsing)
{
	if (parsing->simple_quote == true) // on se trouve deja dans une double quote
		return ALL_OK;
	if (parsing->double_quote == true) // si on est deja dans la quote
		parsing->double_quote = false; // on sort
	else if (parsing->double_quote == false) // si on est pas dans la quote
		parsing->double_quote = true; // on rentre
	 if (parsing->dollar == true) // gérer le dollar ?
	 	save_word(word_length, promptline, i, data, booleans);
	return (ALL_OK);
}
