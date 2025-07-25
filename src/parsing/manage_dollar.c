/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:31:04 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:31:05 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_var_content(char *variable, t_data *data, t_parsing *parsing)
{
	char	*var;
	char	*result;
	char	*env_var;
	t_env	*tmp;

	tmp = data->ls_env;
	var = ft_strtrim(variable, "$");
	if (!var)
		return (pars_err_char(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL));
	result = NULL;
	env_var = search_and_fill_content_with_env(tmp, var, ft_strlen(var));
	if (env_var)
	{
		result = ft_cutstr(env_var, ft_strlen(var) + 1);
		if (!result)
			return (pars_err_char(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL));
	}
	free(var);
	return (result);
}

char	*update_prompt(char *content, int start, t_parsing *parsing)
{
	int		i;
	int		j;
	int		end;
	int		prt;
	char	*new_prompt;

	end = find_var_end(parsing->old_prompt, parsing->p_index);
	prt = ft_strlen(parsing->old_prompt) - (end - start) + (ft_strlen(content));
	new_prompt = malloc(sizeof(char) * (prt + 1));
	if (!new_prompt)
		return (pars_err_char(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL));
	i = 0;
	j = 0;
	while (i < start)
		new_prompt[j++] = parsing->old_prompt[i++];
	while (content && content[j - i])
	{
		new_prompt[j] = content[j - i];
		j++;
	}
	i = end;
	copy_till_the_end(new_prompt, parsing->old_prompt, &i, &j);
	new_prompt[j] = '\0';
	free(parsing->prompt_tab[parsing->pipe_seg]);
	return (new_prompt);
}

static void	init_variable_and_content(t_parsing *parsing, char **content)
{
	char	*variable;

	variable = find_var_name(parsing);
	if (parsing->errcode != ALL_OK)
		return ;
	if (!variable)
		*content = NULL;
	else
		*content = find_var_content(variable, parsing->data, parsing);
	free(variable);
	if (!*content)
	{
		*content = malloc(1);
		if (!*content)
		{
			pars_err_char(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL);
			return ;
		}
		*content[0] = '\0';
	}
}

static void	fill_new_prompt(t_parsing *par, char *content)
{
	int	start;

	start = par->p_index;
	par->old_prompt = par->prompt_tab[par->pipe_seg];
	par->prompt_tab[par->pipe_seg] = NULL;
	par->prompt_tab[par->pipe_seg] = update_prompt(content, start, par);
	free(par->old_prompt);
	par->old_prompt = NULL;
	if (!par->prompt_tab[par->pipe_seg])
		return (parsing_error_void(par, ERR_MALLOC, EXIT_SYSTEM));
	par->p_index = start + ft_strlen(content);
}

void	manage_dollar_sign(t_parsing *parsing)
{
	char	*content;

	content = NULL;
	if (parsing->prompt_tab[parsing->pipe_seg][parsing->p_index + 1] == '?')
	{
		if (handle_exit_status_var(parsing) == 0)
			return ;
	}
	init_variable_and_content(parsing, &content);
	if (parsing->errcode == ALL_OK)
		fill_new_prompt(parsing, content);
	if (content)
		free(content);
}
