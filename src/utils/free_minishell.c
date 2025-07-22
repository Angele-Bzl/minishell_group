/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:32:04 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:32:05 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parsing(t_parsing *parsing)
{
	if (parsing->prompt)
		free(parsing->prompt);
	if (parsing->old_prompt)
		free(parsing->old_prompt);
	if (parsing->prompt_tab)
		free_array(parsing->prompt_tab);
	parsing->prompt = NULL;
}

void	close_free_maybe_exit(t_parsing *parsing, int exitcode)
{
	free_parsing(parsing);
	if (exitcode)
	{
		if (parsing->data->ls_env)
			free_env(parsing->data->ls_env);
		exit(exitcode);
	}
}
