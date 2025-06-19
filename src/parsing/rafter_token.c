# include "minishell.h"

void	update_infile(t_data *data, char *file_name, t_rafter redirection)
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
		infile_lstadd_back(&current, new_in_node);
		current->value = file_name;
		current->redirection = redirection;
	}
}

void	update_outfile(t_data *data, char *file_name, t_rafter redirection)
{
	t_outfile	*new_in_node;
	t_outfile	*current;

	current = data->ls_token->ls_outfile;
	if (current->next == NULL)
	{
		current->value = file_name;
		current->redirection = redirection;
	}
	else
	{
		new_in_node = outfile_lstnew();
		outfile_lstadd_back(&current, new_in_node);
		current->value = file_name;
		current->redirection = redirection;
	}
}

static void manage_simple_rafter(t_data *data, t_parsing *parsing, int *i, char *file_name)
{
	char *prompt;

	prompt = parsing->prompt_tab[*i];
	if (prompt[*i] == '<' && prompt[*i + 1] != '<')
		update_infile(data, file_name, SIMPLE_LEFT);
	if (prompt[*i] == '>' && prompt[*i + 1] != '>' && parsing->outfile_issue == false)
		update_outfile(data, file_name, SIMPLE_RIGHT);
}

static void manage_double_rafter(t_data *data, t_parsing *parsing, int *i, char *file_name)
{
	char *prompt;

	prompt = parsing->prompt_tab[*i];
	if (prompt[*i] == '<')
		update_infile(data, file_name, DOUBLE_LEFT);
	if (prompt[*i] == '>' && parsing->outfile_issue == false)
		update_outfile(data, file_name, DOUBLE_RIGHT);
}

int	manage_rafters(t_data *data, t_parsing *parsing, int *i, char *prompt)
{
	char	*file_name;

	file_name = find_redir_file_name(prompt, *i);
	if (file_name == NULL)
		return (ERR_MALLOC);
	manage_simple_rafter(data, parsing, i, file_name);
	*i = *i + 1;
	manage_double_rafter(data, parsing, i, file_name);
	while (prompt[*i] == ' ' || prompt[*i] == '\t')
	*i = *i + 1;
	return (OK);
}
