# include "minishell.h"

static int	last_pipe_check(char *prompt, int i);

int	prompt_check(char *prompt)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '\'')
			single_quote++;
		if (prompt[i] == '\"')
			double_quote++;
		i++;
	}
	if (single_quote%2 == 1 || double_quote%2 == 1)
		return (-1);
	i--;
	if (last_pipe_check(prompt, i) == 0)
		return (0);
	return (-1);
}

static int	last_pipe_check(char *prompt, int i)
{
	if (prompt[i] != ' ' && prompt[i] != '|')
		return (0);
	if (prompt[i] == '|')
		return (-1);
	i--;
	while (prompt[i])
	{
		if (prompt[i] == '|')
			return (-1);
		if (prompt[i] != ' ')
			return (0);
		i--;
	}
	return (-1);
}
