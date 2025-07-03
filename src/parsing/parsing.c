# include "minishell.h"

static void	errcode_check_in_parsing(t_parsing *parsing)
{
	if (parsing->errcode == ERR_MALLOC)
	{
		free_parsing(parsing);
		exit(EXIT_FAILURE);
	}
	if (parsing->errcode == ERR_PROMPT)
		free_parsing(parsing);
	if (parsing->errcode == ALL_OK)
		free_array(parsing->prompt_tab);
}

void	ft_parsing(t_data *data, t_parsing *parsing)
{
	parsing->errcode = prompt_check(parsing->prompt, parsing);
	if (parsing->errcode == ALL_OK)
		parsing->prompt_tab = pipe_segmentation(parsing, '|');
	if (parsing->errcode == ALL_OK)
		expand_var(parsing);
	if (parsing->errcode == ALL_OK)
		tokenisation(data, parsing);
	errcode_check_in_parsing(parsing);
}
