# include "minishell.h"

int	handle_exit_status_var(t_parsing *parsing)
{
	char	*content;

	parsing->old_prompt = parsing->prompt_tab[parsing->pipe_seg];
	content = ft_itoa(parsing->data->exit_status);
	if (!content)
	{
		parsing->errcode = ERR_MALLOC;
		return (1);
	}
	parsing->prompt_tab[parsing->pipe_seg] = prompt_with_content(content, parsing->p_index, parsing);
	return (0);
}

char	*find_var_name(t_parsing *parsing)
{
	int		i;
	int		start;
	int		end;
	int		var_len;
	char	*var_name;

	start = parsing->p_index + 1;
	end = start;
	if (!first_var_name_char_is_valid(parsing->prompt_tab[parsing->pipe_seg][start]))	// Si le premier charactère de la variable n'est pas valide
	{
		var_name = malloc(sizeof(char) * 2);
		if (!var_name)
		{
			parsing->errcode = ERR_MALLOC;
			return (NULL);
		}
		var_name[0] = parsing->prompt_tab[parsing->pipe_seg][start];
		var_name[1] = '\0';
		return (var_name);
	}
	while (we_are_in_var_name(parsing, parsing->prompt_tab[parsing->pipe_seg][end]))		// Tant qu'on est pas a la fin de notre variable
		end++;
	if (parsing->errcode == ERR_PROMPT)
		return (NULL);
	if (end == start)
		return (NULL);
	var_len = end - start;
	var_name = malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
	{
		parsing->errcode = ERR_MALLOC;
		return (NULL);
	}
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
	if (!first_var_name_char_is_valid(prompt[end]))
	{
		end++;
		return (end);
	}
	while (we_are_in_var_name(NULL, prompt[end]))
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
