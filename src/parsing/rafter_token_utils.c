#include "minishell.h"

char	*extract_file_name(char *prompt, int i, t_parsing *parsing)
{
	int		start;
	int		end;
	int		len;
	char	*file_name;

	start = i;
	while (prompt[i] != '\0' && (!ft_isspace(prompt[i]) && prompt[i] != '>'
		&& prompt[i] != '<'))
	{
		quote_check(prompt[i], parsing);
		while (parsing->double_quote == true || parsing->simple_quote == true)
		{
			i++;
			quote_check(prompt[i], parsing);
		}
		if (prompt[i])
			i++;
	}
	end = i;
	len = end - start;
	file_name = malloc(sizeof(char) * (len + 1));
	if (!file_name)
		return (msg_return_str(MALLOC, NULL, NULL));
	i = 0;
	while (prompt[start + i] && i < len)
	{
		quote_check(prompt[start + i], parsing);
		while ((prompt[start+i] == '\"' && parsing->simple_quote == false)
			|| (prompt[start+i] == '\'' && parsing->double_quote == false))
		{
			start++;
			quote_check(prompt[start + i], parsing);
		}
		file_name[i] = prompt[start + i];
		if (prompt[start + i])
			i++;
		// printf("prompt[i]: %c\n", prompt[start + i]);
	}
	file_name[i] = '\0';
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
