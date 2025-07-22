/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_utils_02.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:30:21 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:30:22 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_till_the_end(char *new_prompt, char *old_prompt, int *i, int *j)
{
	while (old_prompt[*i])
	{
		new_prompt[*j] = old_prompt[*i];
		(*j)++;
		(*i)++;
	}
}
