#include "minishell.h"

int	handle_exit_status_var(t_parsing *par)
{
	char	*content;

	par->old_prompt = par->prompt_tab[par->pipe_seg];
	content = ft_itoa(par->data->exit_status);
	if (!content)
	{
		par->errcode = ERR_MALLOC;
		return (1);
	}
	par->prompt_tab[par->pipe_seg] = update_prompt(content, par->p_index, par);
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
	if (parsing->prompt_tab[parsing->pipe_seg][start] == '\"' || parsing->prompt_tab[parsing->pipe_seg][start] == '\'')
			return (NULL);
	if (!first_char_is_valid(parsing->prompt_tab[parsing->pipe_seg][start]))	// Si le premier charactère de la variable n'est pas valide
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
	while (in_var_name(parsing, parsing->prompt_tab[parsing->pipe_seg][end]))
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
	if (prompt[end] == '\"' || prompt[end] == '\'')
		return (end);
	if (!first_char_is_valid(prompt[end]))
	{
		end++;
		return (end);
	}
	if (prompt[end] == '?')
		end++;
	while (in_var_name(NULL, prompt[end]))
		end++;
	return (end);
}

char	*search_and_fill_content_with_env(t_env *tmp, char *var, int var_len)
{
	char	*env_var;

	env_var = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, var, var_len) && tmp->line[var_len] == '=')
		{
			env_var = tmp->line;
			break ;
		}
		tmp = tmp->next;
	}
	if (!env_var)
		return (NULL);
	return (env_var);
}
