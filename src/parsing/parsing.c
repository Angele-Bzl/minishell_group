/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:31:13 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:31:14 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	errcode_check_parsing(t_parsing *parsing)
{
	if (parsing->errcode == ERR_MALLOC)
	{
		free_token_env(parsing->data);
		free_parsing(parsing);
		exit(EXIT_FAILURE);
	}
	if (parsing->errcode == ERR_PROMPT)
		free_parsing(parsing);
	if (parsing->errcode == ALL_OK)
		free_array(parsing->prompt_tab);
}

void	ft_parsing(t_data *data, t_parsing *parsing)
{
	parsing->errcode = prompt_check(parsing->prompt, parsing, data);
	if (parsing->errcode == ALL_OK)
		parsing->prompt_tab = pipe_segmentation(parsing);
	if (parsing->errcode == ALL_OK)
		expand_var(parsing);
	if (parsing->errcode == ALL_OK)
		tokenisation(data, parsing);
	errcode_check_parsing(parsing);
}
