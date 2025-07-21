#include "minishell.h"

int	in_var_name(t_parsing *parsing, char c)
{
	if (c == '(' || c == ')' || c == '<' || c == '>')
	{
		parsing_error_int(parsing, ERR_PROMPT, EXIT_SYSTEM, 0);
		return (msg_return(ERR_SYNTAX_NEAR, "'(' OR ')' OR '<' OR '>'", 1));
	}
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

int	first_char_is_valid(char c)
{
	if (c == '_' || ft_isalpha(c) || c == '?')
		return (1);
	return (0);
}

char	*fill_var_name(t_parsing *par, int start, int var_len)
{
	int		i;
	char	*var_name;

	var_name = malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		parsg_err_str(par, ERR_MALLOC, EXIT_SYSTEM, NULL);
	i = 0;
	while (i < var_len)
	{
		var_name[i] = par->prompt_tab[par->pipe_seg][start + i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}
