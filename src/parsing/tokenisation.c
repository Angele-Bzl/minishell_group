#include "minishell.h"

static int	find_store_rafters(t_data *data, t_parsing *parsing, char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] != '<' && prompt[i] != '>')
		{
			quote_check(prompt[i], parsing);
			i++;
		}
		if ((prompt[i] == '<' || prompt[i] == '>')
			&& parsing->double_quote == false
			&& parsing->simple_quote == false)
		{
			if (manage_rafter(data, &i, prompt, parsing) == ERR)
				return (ERR);
			while (ft_isspace(prompt[i])
				|| prompt[i] == '<' || prompt[i] == '>')
			{
				quote_check(prompt[i], parsing);
				i++;
			}
		}
		else
		{
			quote_check(prompt[i], parsing);
			i++;
		}
	}
	return (0);
}

static int	find_store_cmds(t_token *current, char *prompt, t_parsing *parsing)
{
	char	*clean_cmds;

	clean_cmds = extract_clean_cmd(parsing, prompt);
	if (!clean_cmds)
		return (ERR);
	current->cmd = split_whitespace_quotes(clean_cmds, ' ', parsing);
	free(clean_cmds);
	if (current->cmd == NULL)
		return (ERR);
	return (0);
}

void	tokenisation(t_data *data, t_parsing *parsing)
{
	int		i;
	t_token	*new_token_node;
	t_token	*current;

	current = data->ls_token;
	i = 0;
	while (parsing->prompt_tab[i])
	{
		if (i > 0)
		{
			new_token_node = token_lstnew();
			if (!new_token_node)
				return (parsing_error_void(parsing, ERR_MALLOC, EXIT_SYSTEM));
			token_lstadd_back(&current, new_token_node);
			current = new_token_node;
		}
		if (find_store_rafters(data, parsing, parsing->prompt_tab[i]) == ERR)
			return ;
		if (find_store_cmds(current, parsing->prompt_tab[i], parsing) == ERR)
			return ;
		i++;
	}
}
