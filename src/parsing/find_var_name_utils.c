# include "minishell.h"

int	we_are_in_var_name(t_parsing *parsing, char c)
{
	if (c == '(' || c == ')' || c == '<' || c == '>')
	{
		// ft_printf_err("minishell: syntax error near unexpected token `%c'\n", c);
		parsing->errcode = ERR_PROMPT;
		return (msg_return(ERR_SYNTAX, &c, 1));// is &c OK ????
		return (1);
	}
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

int first_var_name_char_is_valid(char c)
{
	if (c == '_' || ft_isalpha(c) || c == '?')
		return (1);
	return (0);
}
