# include "minishell.h"

void	find_and_store_all_rafters(t_data *data, t_parsing *parsing, char *prompt)
{
	int	i;

	i = 0;
	while(prompt[i])
	{
		while (prompt[i] != '<' || prompt[i] != '>')
			i++;
		if (prompt[i] == '<' || prompt[i] == '>')
		{
			manage_rafters(data, parsing, &i, prompt);
			while (prompt[i] == ' ' || prompt[i] == '\t')
				i++;
		}
	}
}

void	find_and_store_all_cmds(t_data *data, char *prompt)
{
	int		i;
	char	*clean_cmds;

	clean_cmds = extract_clean_cmd(prompt);
	data->ls_token->cmd = split_whitespace_quotes();
}

int	tokenisation(t_data *data, t_parsing *parsing)
{
	int	k;

	data->ls_token = data->token_head;
	k = 0;
	while (parsing->prompt_tab[k])
	{
		find_and_store_all_rafters(data, parsing, parsing->prompt_tab[k]);
		find_and_store_all_cmds(data, parsing->prompt_tab[k]);
		k++;
		data->ls_token = data->ls_token->next;
	}
}
