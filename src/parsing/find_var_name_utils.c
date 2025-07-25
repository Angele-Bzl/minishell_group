/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_name_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:30:07 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:30:08 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_var_name(t_parsing *parsing, char c)
{
	if (c == '(' || c == ')' || c == '<' || c == '>')
	{
		pars_err_int(parsing, ERR_PROMPT, EXIT_SYSTEM, 0);
		return (msg_return(ERR_SYNTAX_NEAR, "'(' OR ')' OR '<' OR '>'", 1));
	}
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

int	first_char_is_valid(char c)
{
	if (c == '_' || ft_isalpha(c) || c == '?')
		return (1);
	return (0);
}

char	*fill_var_name(t_parsing *par, int start, int var_len)
{
	int		i;
	char	*var_name;

	var_name = malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		pars_err_char(par, ERR_MALLOC, EXIT_SYSTEM, NULL);
	i = 0;
	while (i < var_len)
	{
		var_name[i] = par->prompt_tab[par->pipe_seg][start + i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}
