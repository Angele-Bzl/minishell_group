# include "minishell.h"

static int	skip_io(char *prompt, int i)
{
	i++;
	if (prompt[i] == '<' || prompt[i] == '>')
		i++;
	while (prompt[i] && !ft_isspace(prompt[i]))
		i++;
	while (prompt[i] && ft_isspace(prompt[i]))
		i++;
	return (i);
}

static int	skip_quote_cmd(char *prompt, int *i)
{
	char quote;
	int count = 0;

	quote = prompt[*i];
	count = 0;
	(*i)++; 													// skip quote d'ouverture
	count++;													// prendre en compte les quotes
	while (prompt[*i] && prompt[*i] != quote)
	{
		(*i)++;
		count++;
	}
	if (prompt[*i] == quote)
	{
		(*i)++; 												// skip quote de fermeture
		count++;
	}
	return (count);
}

static int	find_all_cmds_len(char *prompt)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (prompt[i])
	{
		while (ft_isspace(prompt[i]))
			i++;
		if (prompt[i] == '<' || prompt[i] == '>')				// on croise un io.
			i = skip_io(prompt, i);								// avancer jusqu'au prochain arg de de cmd.
		len++;
		while (prompt[i] && !ft_isspace(prompt[i]) && prompt[i] != '<' && prompt[i] != '>')
		{
			if (prompt[i] == '\'' || prompt[i] == '\"')
				len += skip_quote_cmd(prompt, &i);
			else
			{
				i++;
				len++;
			}
		}
	}
	return (len);
}

static char	*extract_current_cmd(char *prompt, int *i, int *j, char *clean_cmd)
{
	char	quote;

	while (prompt[*i] && !ft_isspace(prompt[*i]) && prompt[*i] != '<' && prompt[*i] != '>')
	{
		if (prompt[*i] == '\'' || prompt[*i] == '\"')		// si on croise une quote
		{
			quote = prompt[*i];
			clean_cmd[(*j)++] = prompt[(*i)++];				// ajoute quote ouvrante
			while (prompt[*i] != quote)
				clean_cmd[(*j)++] = prompt[(*i)++];
			if (prompt[*i] == quote)
				clean_cmd[(*j)++] = prompt[(*i)++];			// quote fermante
		}
		else if (prompt[*i])
			clean_cmd[(*j)++] = prompt[(*i)++];
	}
	return (clean_cmd);
}

char	*extract_clean_cmd(char *prompt)
{
	int		i;
	int		j;
	char	*clean_cmd;

	i = 0;
	j = 0;
	clean_cmd = malloc(sizeof(char) * (find_all_cmds_len(prompt) + 1));
	if (!clean_cmd)
		return (NULL);
	while (prompt[i])
	{
		while (ft_isspace(prompt[i]))
			i++;
		if (prompt[i] == '<' || prompt[i] == '>')				// on croise un io
			i = skip_io(prompt, i);								// avancer jusqu'au prochain arg de de cmd.
		extract_current_cmd(prompt, &i, &j, clean_cmd);
		if (prompt[i] && prompt[i] != '<' && prompt[i] != '>')											// ajouter un espace avant le prochain argument
			clean_cmd[j++] = ' ';
	}
	if (j > 0 && clean_cmd[j - 1] == ' ')
		j--;
	clean_cmd[j] = '\0';
	return (clean_cmd);
}
