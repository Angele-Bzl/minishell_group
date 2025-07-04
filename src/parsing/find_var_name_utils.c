# include "minishell.h"

int	we_are_in_var_name(t_parsing *parsing, char c)
{
	if (c == '(' || c == ')' || c == '<' || c == '>')
	{
		parsing->errcode = ERR_PROMPT;
		return (msg_return(ERR_SYNTAX_NEAR, ft_strdup("'(' OR ')' OR '<' OR '>'"), 1)); //if malloc ft_strdup faild -> it's ok
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
