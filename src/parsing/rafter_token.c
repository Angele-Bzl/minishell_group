# include "minishell.h"

static int	update_file(t_file *ls_file, char *file_name, t_rafter redirection)
{
	t_file	*new_in_node;

	if (ls_file && ls_file->value == NULL)
	{
		ls_file->value = file_name;
		ls_file->redirection = redirection;
	}
	else
	{
		new_in_node = file_lstnew();
		if (!new_in_node)
			return (-1);
		new_in_node->value = file_name;
		new_in_node->redirection = redirection;
		file_lstadd_back(&ls_file, new_in_node);
	}
	return (0);
}

static int check_rafter(t_data *data, char *file_name, char *prompt, int i)
{
	t_token *current;

	current = token_lstlast(data->ls_token);
	if (prompt[i] == '<' && prompt[i + 1] != '<')
		if (update_file(current->ls_infile, file_name, SIMPLE_LEFT) == -1)
			return (-1);
	if (prompt[i] == '>' && prompt[i + 1] != '>')
		if (update_file(current->ls_outfile, file_name, SIMPLE_RIGHT) == -1)
			return (-1);
	if (prompt[i + 1] == '<')
		if (update_file(current->ls_infile, file_name, DOUBLE_LEFT) == -1)
			return (-1);
	if (prompt[i + 1] == '>')
		if (update_file(current->ls_outfile, file_name, DOUBLE_RIGHT) == -1)
			return (-1);
	return (0);
}

int	manage_rafters(t_data *data, int *i, char *prompt)
{
	char	*file_name;

	file_name = find_redir_file_name(prompt, *i);
	if (file_name == NULL)
		return (-1);
	if (check_rafter(data, file_name, prompt, *i) == -1)
		return (-1);
	if (prompt[*i + 1] == '<' || prompt[*i + 1] == '>')
		*i = *i + 1;
	while (ft_isspace(prompt[*i]))
		*i = *i + 1;
	return (0);
}
