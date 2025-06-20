# include "minishell.h"

char	*find_var_name(t_parsing *parsing)
{
	int		i;
	int		start;
	int		end;
	int		var_len;
	char	*var_name;

	start = parsing->p_index + 1;
	end = start;
	while (!isspace(parsing->prompt_tab[parsing->pipe_seg][end]) && parsing->prompt_tab[parsing->pipe_seg][end] != '\'' && parsing->prompt_tab[parsing->pipe_seg][end] != '\"'
		&& parsing->prompt_tab[parsing->pipe_seg][end] != '$' && parsing->prompt_tab[parsing->pipe_seg][end] != '\0')		// Tant qu'on est pas a la fin de notre variable
		end++;
	var_len = end - start;
	var_name = malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < var_len)
	{
		var_name[i] = parsing->prompt_tab[parsing->pipe_seg][start + i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

int	find_var_end(char *prompt, int p_index)
{
	int	end;

	end = p_index + 1;
	while (!ft_isspace(prompt[end]) && prompt[end] != '\'' && prompt[end] != '\"'
		&& prompt[end] != '$' && prompt[end] != '\0')
		end++;
	return (end);
}

char	*search_and_fill_content_with_env(t_env *tmp, char *var, int var_len)
{
	char *env_var;

	env_var = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, var, var_len) && tmp->line[var_len] == '=')
		{
			env_var = tmp->line;
			break;
		}
		tmp = tmp->next;
	}
	if (!env_var) 											//si la variable existe pas c'est = NULL mais c'est pas un fail
		return (NULL);
	return (env_var);
}
