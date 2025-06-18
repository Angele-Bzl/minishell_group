# include "minishell.h"

static void	errcode_check_in_parsing(int *errcode, t_parsing *parsing)
{
	if (*errcode == ERR_MALLOC)											// on free + quitte le prog
	{
		free_all(parsing);
		exit(EXIT_FAILURE);
	}
	if (*errcode == ERR_PROMPT)											// on free + continue avec new prompt
		free_all(parsing);
}

static int	fill_prompt_tab(t_parsing *parsing)
{
	int	errcode;

	errcode = OK;
	parsing->prompt_tab = pipe_segmentation(parsing->prompt, '|', &errcode);		// créer le prompt_tab et print les erreurs
	return (errcode);
}

void	ft_parsing(t_data *data, t_parsing *parsing, int *errcode)
{
	*errcode = prompt_check(parsing->prompt, parsing);					// check si le prompt a des quotes ouverte ou finit par un pipe. Ne pas gerer les cas de heredoc
	if (*errcode == OK)
		*errcode = fill_prompt_tab(parsing);
	if (*errcode == OK)
		*errcode = expand_var(parsing);							// si mauvais, expand et on free
	if (*errcode == OK)
		*errcode = tokenisation(data, parsing);
	errcode_check_in_parsing(errcode, parsing);
}

// si result = MALLOC_ERROR(-42), on exit après free.
// si result = PROMPT_ERROR(-1), on free le prompt actuel et on continue.
// si result = OK(1), on continue.
