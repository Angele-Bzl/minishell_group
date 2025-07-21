#include "minishell.h"

char	*extract_file_name(char *prompt, int i, t_parsing *parsing)
{
	int	start;
	int	count_quote;
	int	len;
	char *file_name;
	int j;

	count_quote = 0;
	while (prompt[i] && ft_isspace(prompt[i]))
		i++;
	start = i;
	while (prompt[i] && !ft_isspace(prompt[i]) && prompt[i] != '>' && prompt[i] != '<')
	{
		if (quote_check(prompt[i], parsing) == 1)
			count_quote++;
		while (parsing->double_quote == true || parsing->simple_quote == true)
		{
			i++;
			if (quote_check(prompt[i], parsing) == 0)
				count_quote++;
		}
		i++;
	}
	len = i - start - count_quote;
	file_name = malloc(sizeof(char) * (len + 1));
	if (!file_name)
		return (msg_return_str(MALLOC, NULL, NULL));
	j = 0;
	while (prompt[start] && j < len)
	{
		while (quote_check(prompt[start], parsing) != -1)
			start++;
		while (parsing->double_quote == true || parsing->simple_quote == true)
		{
			if (quote_check(prompt[start], parsing) == 0)
			{
				start++;
				break;
			}
			file_name[j] = prompt[start];
			j++;
			start++;
		}
		while (quote_check(prompt[start], parsing) != -1)
			start++;
		if (prompt[start] && j < len)
		{
			file_name[j] = prompt[start];
			j++;
			start++;
		}
	}
	file_name[j] = '\0';
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
