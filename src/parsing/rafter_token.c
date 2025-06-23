# include "minishell.h"

static int	update_infile(t_parsing *parsing, t_data *data, char *file_name, t_rafter redirection)
{
	t_infile	*new_in_node;
	t_token		*current_token;

	current_token = token_lstlast(data->ls_token);
	if (current_token->ls_infile && current_token->ls_infile->value == NULL)
	{
		current_token->ls_infile->value = file_name;
		current_token->ls_infile->redirection = redirection;
	}
	else
	{
		new_in_node = infile_lstnew();
		if (!new_in_node)
		{
			parsing->errcode = ERR_MALLOC;
			return (-1);
		}
		new_in_node->value = file_name;
		new_in_node->redirection = redirection;
		infile_lstadd_back(&current_token->ls_infile, new_in_node);
	}
	return (0);
}

static int	update_outfile(t_parsing *parsing, t_data *data, char *file_name, t_rafter redirection)
{
	t_outfile	*new_out_node;
	t_token		*current_token;

	current_token = token_lstlast(data->ls_token);
	if (current_token->ls_outfile && current_token->ls_outfile->value == NULL)
	{
		current_token->ls_outfile->value = file_name;
		current_token->ls_outfile->redirection = redirection;
	}
	else
	{
		new_out_node = outfile_lstnew();
		if (!new_out_node)
		{
			parsing->errcode = ERR_MALLOC;
			return (-1);
		}
		new_out_node->value = file_name;
		new_out_node->redirection = redirection;
		outfile_lstadd_back(&current_token->ls_outfile, new_out_node);
	}
	return (0);
}

static int manage_simple_rafter(t_data *data, t_parsing *parsing, char *file_name, char *rafter)
{
	if (rafter[0] == '<' && rafter[1] != '<')
		if (update_infile(parsing, data, file_name, SIMPLE_LEFT) == -1)
			return (-1);
	if (rafter[0] == '>' && rafter[1] != '>' && parsing->outfile_issue == false)
		if (update_outfile(parsing, data, file_name, SIMPLE_RIGHT) == -1)
			return (-1);
	return (0);
}

static int manage_double_rafter(t_data *data, t_parsing *parsing, char *file_name, char *rafter)
{
	if (rafter[0] == '<')
		if (update_infile(parsing, data, file_name, DOUBLE_LEFT) == -1)
			return (-1);
	if (rafter[0] == '>' && parsing->outfile_issue == false)
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
	if (manage_simple_rafter(data, parsing, file_name, prompt + *i) == -1)
		return (-1);
	*i = *i + 1;
	if (manage_double_rafter(data, parsing, file_name, prompt + *i) == -1)
		return (-1);
	while (ft_isspace(prompt[*i]))
		*i = *i + 1;
	return (0);
}
