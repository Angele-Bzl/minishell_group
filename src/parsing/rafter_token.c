# include "minishell.h"

static int	update_infile(t_parsing *parsing, t_data *data, char *file_name, t_rafter redirection)
{
	t_infile	*new_in_node;
	t_infile	*current;

	current = data->ls_token->ls_infile;
	if (current->next == NULL)
	{
		current->value = file_name;
		current->redirection = redirection;
	}
	else
	{
		new_in_node = infile_lstnew();
		if (!new_in_node)
		{
			parsing->errcode = ERR_MALLOC;
			return (-1);
		}
		infile_lstadd_back(&current, new_in_node);
		current->value = file_name;
		current->redirection = redirection;
	}
	return (0);
}

static int	update_outfile(t_parsing *parsing, t_data *data, char *file_name, t_rafter redirection)
{
	t_outfile	*new_out_node;
	t_outfile	*current;

	current = data->ls_token->ls_outfile;
	if (current->next == NULL)
	{
		current->value = file_name;
		current->redirection = redirection;
	}
	else
	{
		new_out_node = outfile_lstnew();
		if (!new_out_node)
		{
			parsing->errcode = ERR_MALLOC;
			return (-1);
		}
		outfile_lstadd_back(&current, new_out_node);
		current->value = file_name;
		current->redirection = redirection;
	}
	return (0);
}

static int manage_simple_rafter(t_data *data, t_parsing *parsing, int *i, char *file_name)
{
	char *prompt;

	prompt = parsing->prompt_tab[*i];
	if (prompt[*i] == '<' && prompt[*i + 1] != '<')
		if (update_infile(parsing, data, file_name, SIMPLE_LEFT) == -1)
			return (-1);
	if (prompt[*i] == '>' && prompt[*i + 1] != '>' && parsing->outfile_issue == false)
		if (update_outfile(parsing, data, file_name, SIMPLE_RIGHT) == -1)
			return (-1);
	return (0);
}

static int manage_double_rafter(t_data *data, t_parsing *parsing, int *i, char *file_name)
{
	char *prompt;

	prompt = parsing->prompt_tab[*i];
	if (prompt[*i] == '<')
		if (update_infile(parsing, data, file_name, DOUBLE_LEFT) == -1)
			return (-1);
	if (prompt[*i] == '>' && parsing->outfile_issue == false)
		if (update_outfile(parsing, data, file_name, DOUBLE_RIGHT) == -1)
			return (-1);
	return (0);
}

int	manage_rafters(t_data *data, t_parsing *parsing, int *i, char *prompt)
{
	char	*file_name;

	file_name = find_redir_file_name(prompt, *i);
	if (file_name == NULL)
	{
		parsing->errcode = ERR_MALLOC;
		return (-1);
	}
	if (manage_simple_rafter(data, parsing, i, file_name) == -1)
		return (-1);
	*i = *i + 1;
	if (manage_double_rafter(data, parsing, i, file_name) == -1)
		return (-1);
	while (prompt[*i] == ' ' || prompt[*i] == '\t')
	*i = *i + 1;
	return (0);
}
