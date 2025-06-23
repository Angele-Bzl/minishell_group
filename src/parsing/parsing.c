# include "minishell.h"

static void	errcode_check_in_parsing(t_parsing *parsing)
{
	if (parsing->errcode == ERR_MALLOC)											// on free + quitte le prog
	{
		free_all(parsing);
		exit(EXIT_FAILURE);
	}
	if (parsing->errcode == ERR_PROMPT)											// on free + continue avec new prompt
		free_all(parsing);
}

void	ft_parsing(t_data *data, t_parsing *parsing)
{
	parsing->errcode = prompt_check(parsing->prompt, parsing);					// check si le prompt a des quotes ouverte ou finit par un pipe. Ne pas gerer les cas de heredoc
	if (parsing->errcode == ALL_OK)
		parsing->prompt_tab = pipe_segmentation(parsing, '|');
	if (parsing->errcode == ALL_OK)
		expand_var(parsing);							// si mauvais, expand et on free
	if (parsing->errcode == ALL_OK)
		tokenisation(data, parsing);
	errcode_check_in_parsing(parsing);
}

// si result = MALLOC_ERROR(-42), on exit après free.
// si result = PROMPT_ERROR(-1), on free le prompt actuel et on continue.
// si result = OK(1), on continue.
