# include "minishell.h"

static void	find_and_store_all_rafters(t_data *data, t_parsing *parsing, char *prompt)
{
	int	i;

	i = 0;
	while(prompt[i])
	{
		while (prompt[i] && prompt[i] != '<' && prompt[i] != '>')
			i++;
		if (prompt[i] == '<' || prompt[i] == '>')
		{
			manage_rafters(data, parsing, &i, prompt);
			while (prompt[i] == ' ' || prompt[i] == '\t')
				i++;
		}
	}
}

static void	find_and_store_all_cmds(t_data *data, char *prompt)
{
	char	*clean_cmds;

	clean_cmds = extract_clean_cmd(prompt);
	data->ls_token->cmd = split_whitespace_quotes(clean_cmds, ' ');
}

int	tokenisation(t_data *data, t_parsing *parsing)						// remplir chacuns des noeuds de ls_token
{
	int	i;
	t_token	*new_token_node;

	data->ls_token = data->token_head;
	i = 0;
	while (parsing->prompt_tab[i])
	{
		new_token_node = token_lstnew();
		if (!new_token_node)
			return (1);
		find_and_store_all_rafters(data, parsing, parsing->prompt_tab[i]);
		find_and_store_all_cmds(data, parsing->prompt_tab[i]);
		token_lstadd_back(&data->token_head, new_token_node);
		data->ls_token = new_token_node;
		printf()
		i++;
	}
	return (0);
}
