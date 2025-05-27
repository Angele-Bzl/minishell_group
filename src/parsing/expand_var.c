# include "minishell.h"

int	expand_var(t_data *data, t_parsing *parsing)										// partie expand, "go!". checker si on est dans une quote.
{
	parsing->pipe_seg = 0;
	parsing->p_index = 0;
	while (parsing->prompt_tab[parsing->pipe_seg])										// tant qu'on a un seg_pipe
	{
		while (parsing->prompt_tab[parsing->pipe_seg][parsing->p_index])				// tant qu'on a des charactères dans le seg_pipe actuel
		{
			if (parsing->prompt_tab[parsing->pipe_seg][parsing->p_index] == '$')
			{
				if (manage_dollar(data, parsing) == -1)									// créer un nouveau prompt avec le contenu de la var croisée
					return (-1);
				parsing->p_index--;														// sécuriser le cas où la var remplacée est plus longue que son contenu
			}
			parsing->p_index++;
		}
		parsing->pipe_seg++;
		parsing->p_index = 0;
	}
	return (0);
}
