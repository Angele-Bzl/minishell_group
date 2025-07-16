#include "minishell.h"

int	prompt_begins_with_a_pipe(const char *prompt, int *i)
{
	while (ft_isspace(prompt[*i]))
		(*i)++;
	if (prompt[*i] == '|')
		return (msg_return(ERR_SYNTAX_NEAR, "|", ERR));
	return (0);
}

int	parse_pipe_segments(char const *s, int i)
{
	int	count;

	count = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		while (s[i] != '|' && s[i] != '\0')
		{
			if (s[i] == '\"' || s[i] == '\'')
				skip_quote(s, &i);
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
