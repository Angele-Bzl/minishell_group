# include "minishell.h"

int	prompt_begins_with_a_pipe(const char *prompt, int *i, t_parsing *parsing)
{
	while (ft_isspace(prompt[*i]))
		(*i)++;
	if (prompt[*i] == '|')
	{
		parsing->errcode = ERR_PROMPT;
		return (msg_return(ERR_SYNTAX_NEAR, "|", ERR));
	}
	return (0);
}

int	parse_pipe_segments(char const *s, int i)
{
	int count;

	count = 0;
	while (s[i])
	{
		while (ft_isspace(s[i])) 							//il faudra plutot mettre is space ici
			i++;
		while (s[i] != '|' && s[i] != '\0')
		{
			if (s[i] == '\"' || s[i] == '\'')
				skip_quote(s, &i); 							// si s[i] = quote, on continue jusqu'a la prochaine
			i++;
		}
		if (s[i] != '\0')
		{
			count++;
			i++;
		}
	}
	return (count);
}
