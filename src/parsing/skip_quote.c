/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:31:36 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:31:37 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quote(const char *str, int *i)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		while (str[*i] != '\"')
		{
			*i = *i + 1;
		}
		return (*i + 1);
	}
	else if (str[*i] == '\'')
	{
		*i = *i + 1;
		while (str[*i] != '\'')
		{
			*i = *i + 1;
		}
		return (*i + 1);
	}
	return (*i + 1);
}
