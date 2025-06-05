# include "minishell.h"

static char	*find_redir_file_name(char *prompt, int i)
{
	char	*file_name;
	int		len;
	int		start;
	int		end;
	i++;

	while (ft_isspace(prompt[i]))										// on saute les espaces
		i++;
	start = i;
	while (!ft_isspace(prompt[i]) && prompt[i] != '\0')					// on va jusqu'à la fin du nom
		i++;
	end = i;
	len = end - start;
	file_name = malloc(sizeof(char) * (len + 1));
	if (!file_name)
		return (NULL);
	i = 0;
	while (i < len)														// copie du nom dp le prompt sur "len" characteres
	{
		file_name[i] = prompt[start + i];
		i++;
	}
	file_name[i] = '\0';
	return (file_name);
}

static void	manage_outfile(t_data *data, t_parsing *parsing, char *file_name)
{
	if (*data->ls_token->io_redir[1] == SIMPLE_RIGHT)
	{
		if (!open(file_name, O_CREAT))
			parsing->outfile_issue = TRUE;
	}
	else if (*data->ls_token->io_redir[1] == DOUBLE_RIGHT)
	{
		if (!open(file_name, O_APPEND | O_CREAT))
			parsing->outfile_issue = TRUE;
	}
}

void	manage_rafters(t_data *data, t_parsing *parsing, int *i, char *prompt)
{
	char	*file_name;

	file_name = find_redir_file_name(prompt, *i);
	if (prompt[*i] == '<')
	{
		data->ls_token->io_value[0] = file_name;
		*data->ls_token->io_redir[0] = SIMPLE_LEFT;
	}
	if (prompt[*i] == '>' && parsing->outfile_issue == false)
	{
		data->ls_token->io_value[1] = file_name;
		*data->ls_token->io_redir[1] = SIMPLE_RIGHT;
	}
	*i = *i + 1;
	if (prompt[*i] == '<')
		*data->ls_token->io_redir[0] = DOUBLE_LEFT;
	if (prompt[*i] == '>' && parsing->outfile_issue == false)
	{
		data->ls_token->io_value[1] = file_name;
		*data->ls_token->io_redir[1] = DOUBLE_RIGHT;
	}
	while (prompt[*i] == ' ' || prompt[*i] == '\t')
		*i = *i + 1;
	if (parsing->outfile_issue == false)
		manage_outfile(data, parsing, file_name);
}
