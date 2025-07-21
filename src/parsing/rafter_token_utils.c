#include "minishell.h"

char	*extract_file_name(char *prompt, int i, t_parsing *parsing)
{
	int		start;
	int		end;
	int		len;
	char	*file_name;

	start = i;
	while ( prompt[i] != '\0' && prompt[i] != '>'&& prompt[i] != '<')
	{
		if (!ft_isspace(prompt[i]) && parsing->double_quote == false
		&& parsing->simple_quote == false)
			break ;
		quote_check(prompt[i], parsing);
		i++;
	}
	end = i;
	len = end - start;
	file_name = malloc(sizeof(char) * (len + 1));
	if (!file_name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		file_name[i] = prompt[start + i];
		i++;
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
		parsg_err_str(parsing, ERR_PROMPT, EXIT_SYSTEM, NULL);
		return (msg_return_str(ERR_SYNTAX_NEAR, "'<' OR '>' OR '\\0'", NULL));
	}
	file_name = extract_file_name(prompt, i, parsing);
	if (!file_name)
		return (parsg_err_str(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL));
	return (file_name);
}
