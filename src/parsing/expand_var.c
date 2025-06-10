# include "minishell.h"

int	dollar_remaining(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	quote_check(char c, t_parsing *parsing)
{
	if (c == '\"' && parsing->double_quote == false && parsing->simple_quote == false)
		parsing->double_quote = true;
	else if (c == '\"' && parsing->double_quote == true && parsing->simple_quote == false)
		parsing->double_quote = false;
	else if (c == '\'' && parsing->simple_quote == false && parsing->double_quote == false)
		parsing->simple_quote = true;
	else if (c == '\'' && parsing->simple_quote == true && parsing->double_quote == false)
		parsing->simple_quote = false;
}

int	expand_var(t_data *data, t_parsing *parsing)										// partie expand, "go!". checker si on est dans une quote.
{
	parsing->pipe_seg = 0;
	parsing->p_index = 0;
	while (parsing->prompt_tab[parsing->pipe_seg])										// tant qu'on a un seg_pipe
	{
		while (parsing->prompt_tab[parsing->pipe_seg][parsing->p_index])				// tant qu'on a des charactères dans le seg_pipe actuel
		{
			//printf("expand_var : %s\n", parsing->prompt_tab[parsing->pipe_seg]);
			quote_check(parsing->prompt_tab[parsing->pipe_seg][parsing->p_index], parsing);
			if (parsing->prompt_tab[parsing->pipe_seg][parsing->p_index] == '$' && parsing->simple_quote == false)
			{
				if (manage_dollar(data, parsing) == -1)									// créer un nouveau prompt avec le contenu de la var croisée
					return (-1);
			}
			parsing->p_index++;
		}
		if (!dollar_remaining(parsing->prompt_tab[parsing->pipe_seg]))
			parsing->pipe_seg++;
		parsing->p_index = 0;
	}
	return (0);
}
