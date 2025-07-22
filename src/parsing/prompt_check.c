/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:31:23 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:31:24 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	last_pipe_check(char *prompt)
{
	int	i;

	i = ft_strlen(prompt) - 1;
	if (prompt[i] != ' ' && prompt[i] != '|')
		return (OK);
	if (prompt[i] == '|')
		return (msg_return(ERR_SYNTAX_PIPE, NULL, ERR_PROMPT));
	i--;
	while (prompt[i])
	{
		if (prompt[i] == '|')
			return (msg_return(ERR_SYNTAX_PIPE, NULL, ERR_PROMPT));
		if (prompt[i] != ' ')
			return (OK);
		i--;
	}
	return (OK);
}

static int	quote_count(char *prompt, t_parsing *parsing)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (prompt[i] != '\0')
	{
		quote_check(prompt[i], parsing);
		if (prompt[i] == '\'' && parsing->double_quote == false)
			single_quote++;
		if (prompt[i] == '\"' && parsing->simple_quote == false)
			double_quote++;
		i++;
	}
	if (single_quote % 2 == 1 || double_quote % 2 == 1)
		return (msg_return(ERR_SYNTAX_QUOTE, NULL, ERR_PROMPT));
	return (OK);
}

int	prompt_check(char *prompt, t_parsing *parsing, t_data *data)
{
	if (quote_count(prompt, parsing) == ERR_PROMPT
		|| last_pipe_check(prompt) == ERR_PROMPT)
	{
		data->exit_status = 2;
		return (ERR_PROMPT);
	}
	return (OK);
}
