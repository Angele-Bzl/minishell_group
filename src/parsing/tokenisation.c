#include "minishell.h"

static int	find_and_store_all_rafters(t_data *data, t_parsing *parsing, char *prompt)
{
	int	i;

	i = 0;
	while(prompt[i])
	{
		while (prompt[i] && prompt[i] != '<' && prompt[i] != '>')
			i++;
		if (prompt[i] == '<' || prompt[i] == '>')
		{
			if (manage_rafters(data, parsing, &i, prompt) == ERR_MALLOC)
				return (ERR_MALLOC);
			while (prompt[i] == ' ' || prompt[i] == '\t' || prompt[i] == '<' ||  prompt[i] == '>')
				i++;
		}
	}
	return (OK);
}

static int	find_and_store_all_cmds(t_token *current, char *prompt, t_parsing *parsing)
{
	char	*clean_cmds;

	clean_cmds = extract_clean_cmd(prompt);
	if (!clean_cmds)
		return (ERR_MALLOC);
	current->cmd = split_whitespace_quotes(clean_cmds, ' ', parsing);
	return (OK);
}

void	tokenisation(t_data *data, t_parsing *parsing)		// remplir chacuns des noeuds de ls_token
{
	int		i;
	t_token	*new_token_node;
	t_token	*current;

	current = data->ls_token;
	i = 0;
	if (parsing->prompt_tab[i])
	{
        if (find_and_store_all_rafters(data, parsing, parsing->prompt_tab[i]) == ERR_MALLOC)
			return;
        if (find_and_store_all_cmds(current, parsing->prompt_tab[i], parsing) == ERR_MALLOC)
			return;
		i++;
		// printf("TOKEN data ls token cmd 0 = %s | address token = %p\n", data->ls_token->cmd[0], data->ls_token);
    }
	while (parsing->prompt_tab[i])
	{
		new_token_node = token_lstnew();
		if (!new_token_node)
		{
			parsing->errcode = ERR_MALLOC;
			return;
		}
		token_lstadd_back(&current, new_token_node);
		current = new_token_node;
		if (find_and_store_all_rafters(data, parsing, parsing->prompt_tab[i]) == ERR_MALLOC)
			return;
		if (find_and_store_all_cmds(current, parsing->prompt_tab[i], parsing) == ERR_MALLOC)
			return;
		i++;
		// printf("TOKEN data ls token cmd 0 = %s | address token = %p\n", data->ls_token->cmd[0], data->ls_token);
	}
	return (OK);
}
