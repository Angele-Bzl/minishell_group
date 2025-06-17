# include "minishell.h"

int	prompt_begins_with_a_pipe(const char *s, int *i, int *errcode)
{
	while (ft_isspace(s[*i]))
		(*i)++;
	if (s[*i] == '|')
	{
		printf("syntax error near unexpected token '|'\n");
		*errcode = ERR_PROMPT;
		return (ERR_PROMPT);
	}
	return (OK);
}

int	parse_pipe_segments(char const *s, char c, int i)
{
	int count;

	count = 0;
	while (s[i])
	{
		while (ft_isspace(s[i])) 							//il faudra plutot mettre is space ici
			i++;
		while (s[i] != c && s[i] != '\0')
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
