/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:31:00 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:31:01 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
	free(content);
	return (0);
}

static char	*first_char_not_valid(t_parsing *par, int start)
{
	char	*var_name;

	var_name = malloc(sizeof(char) * 2);
	if (!var_name)
		return (pars_err_char(par, ERR_MALLOC, EXIT_SYSTEM, NULL));
	var_name[0] = par->prompt_tab[par->pipe_seg][start];
	var_name[1] = '\0';
	return (var_name);
}

char	*find_var_name(t_parsing *par)
{
	int		start;
	int		end;
	int		var_len;
	char	*var_name;

	start = par->p_index + 1;
	end = start;
	if (par->prompt_tab[par->pipe_seg][start] == '\"'
		|| par->prompt_tab[par->pipe_seg][start] == '\'')
		return (NULL);
	if (!first_char_is_valid(par->prompt_tab[par->pipe_seg][start]))
		return (first_char_not_valid(par, start));
	while (in_var_name(par, par->prompt_tab[par->pipe_seg][end]))
		end++;
	if (par->errcode == ERR_PROMPT || end == start)
		return (NULL);
	var_len = end - start;
	var_name = fill_var_name(par, start, var_len);
	if (!var_name)
		return (NULL);
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
	{
		end++;
		return (end);
	}
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
