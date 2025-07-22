/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:29:08 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:29:13 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_all_cmds(char *clean_cmd, char *prompt, t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prompt[i])
	{
		while (ft_isspace(prompt[i]))
			i++;
		if (prompt[i] == '<' || prompt[i] == '>')
			i = skip_io(prompt, i, parsing);
		extract_current_cmd(prompt, &i, &j, clean_cmd);
		if (prompt[i] && prompt[i] != '<' && prompt[i] != '>')
			clean_cmd[j++] = ' ';
	}
	if (j > 0 && clean_cmd[j - 1] == ' ')
		j--;
	clean_cmd[j] = '\0';
}
