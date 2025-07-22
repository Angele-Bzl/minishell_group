#include "minishell.h"

static int	find_name_len(t_parsing *par, char *prompt, int i)
{
	int	len;
	int	start;
	int	count_quote;

	count_quote = 0;
	while (prompt[i] && ft_isspace(prompt[i]))
		i++;
	start = i;
	while (prompt[i] && !ft_isspace(prompt[i])
		&& prompt[i] != '>' && prompt[i] != '<')
	{
		if (quote_check(prompt[i], par) == 1)
			count_quote++;
		while (par->double_quote == true || par->simple_quote == true)
		{
			i++;
			if (quote_check(prompt[i], par) == 0)
				count_quote++;
		}
		i++;
	}
	len = i - start - count_quote;
	return (len);
}

static int	skip_quotes(t_parsing *par, char *prompt, int j)
{
	while (prompt[j] && quote_check(prompt[j], par) != -1)
		j++;
	return (j);
}

static void	fill_file_name(t_parsing *par, char *prompt, int j, char *file_name)
{
	int	i;
	int	len;

	len = find_name_len(par, prompt, j);
	while (prompt[j] && ft_isspace(prompt[j]))
		j++;
	i = 0;
	while (prompt[j] && i < len)
	{
		j = skip_quotes(par, prompt, j);
		while (par->double_quote == true || par->simple_quote == true)
		{
			if (quote_check(prompt[j], par) == 0)
			{
				j++;
				break ;
			}
			file_name[i++] = prompt[j++];
		}
		j = skip_quotes(par, prompt, j);
		if (prompt[j] && i < len)
			file_name[i++] = prompt[j++];
	}
	file_name[i] = '\0';
}

char	*extract_file_name(char *prompt, int start, t_parsing *parsing)
{
	int		len;
	char	*file_name;

	len = find_name_len(parsing, prompt, start);
	file_name = malloc(sizeof(char) * (len + 1));
	if (!file_name)
		return (msg_return_str(MALLOC, NULL, NULL));
	fill_file_name(parsing, prompt, start, file_name);
	return (file_name);
}

char	*find_redir_file_name(char *prompt, int i, t_parsing *parsing)
{
	char	*file_name;

	i++;
	if (prompt[i] == prompt[i - 1])
		i++;
	while (ft_isspace(prompt[i]))
		i++;
	if (prompt[i] == '<' || prompt[i] == '>' || prompt[i] == '\0')
	{
		parsing_error_char(parsing, ERR_PROMPT, EXIT_SYSTEM, NULL);
		return (msg_return_str(ERR_SYNTAX_NEAR, "'<' OR '>' OR '\\0'", NULL));
	}
	file_name = extract_file_name(prompt, i, parsing);
	if (!file_name)
		return (parsing_error_char(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL));
	return (file_name);
}
