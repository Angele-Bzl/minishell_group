#include "minishell.h"

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
			return (ERR);
		new_in_node->value = file_name;
		new_in_node->redirection = redirection;
		file_lstadd_back(&ls_file, new_in_node);
	}
	return (0);
}

static int	check_rafter(t_parsing *par, char *file_name, char *prompt, int i)
{
	t_token	*current;

	current = token_lstlast(par->data->ls_token);
	if (prompt[i] == '<' && prompt[i + 1] != '<')
		if (update_file(current->ls_infile, file_name, SIMPLE_LEFT) == ERR)
			return (ERR);
	if (prompt[i] == '>' && prompt[i + 1] != '>')
		if (update_file(current->ls_outfile, file_name, SIMPLE_RIGHT) == ERR)
			return (ERR);
	if (prompt[i + 1] == '<')
	{
		file_name = here_doc(file_name, par);
		if (!file_name)
			return (ERR);
		if (update_file(current->ls_infile, file_name, DOUBLE_LEFT) == ERR)
			return (ERR);
	}
	if (prompt[i + 1] == '>')
		if (update_file(current->ls_outfile, file_name, DOUBLE_RIGHT) == ERR)
			return (ERR);
	return (OK);
}

int	manage_rafter(t_data *data, int *i, char *prompt, t_parsing *parsing)
{
	char	*file_name;

	(void)data;
	file_name = find_redir_file_name(prompt, *i, parsing);
	if (file_name == NULL)
		return (ERR);
	if (check_rafter(parsing, file_name, prompt, *i) == ERR)
	{
		if (parsing->errcode == ERR_PROMPT)
			return (ERR);
		else
			return (parsing_error_int(parsing, ERR_MALLOC, EXIT_SYSTEM, ERR));
	}
	if (prompt[*i + 1] == '<' || prompt[*i + 1] == '>')
		*i = *i + 1;
	while (ft_isspace(prompt[*i]))
		*i = *i + 1;
	return (0);
}
