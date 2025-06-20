# include "minishell.h"

char	*extract_file_name(char *prompt, int i)					// trouver le debut/fin du nom et le renvoyer
{
	int		start;
	int		end;
	int		len;
	char	*file_name;

	start = i;
	while (!ft_isspace(prompt[i]) && prompt[i] != '\0')
		i++;
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

char	*find_redir_file_name(char *prompt, int i)				// on avance jusqu'au début du nom pour l'extraire.
{
	char	*file_name;

	i++;
	if (prompt[i] == '<' || prompt[i] == '>')
		i++;
	while (ft_isspace(prompt[i]))
		i++;
	if (prompt[i] == '<' || prompt[i] == '>')
	{
		printf("bash: syntax error near unexpected token '%c'\n", prompt[i]);
		return (NULL);
	}
	file_name = extract_file_name(prompt, i);
	if (!file_name)
		return (NULL);
	return (file_name);
}

