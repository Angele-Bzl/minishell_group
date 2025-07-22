/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:29:42 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:29:43 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_io(char *prompt, int i, t_parsing *parsing)
{
	i++;
	if (prompt[i] == '<' || prompt[i] == '>')
		i++;
	while (prompt[i] && ft_isspace(prompt[i]))
		i++;
	while (prompt[i] && !ft_isspace(prompt[i]))
	{
		quote_check(prompt[i], parsing);
		i++;
		while (ft_isspace(prompt[i])
			&& (parsing->double_quote == true
				|| parsing->simple_quote == true))
		{
			quote_check(prompt[i], parsing);
			i++;
		}
	}
	while (prompt[i] && ft_isspace(prompt[i]))
		i++;
	return (i);
}

static int	skip_quote_cmd(char *prompt, int *i)
{
	char	quote;
	int		count;

	quote = prompt[*i];
	count = 0;
	(*i)++;
	count++;
	while (prompt[*i] && prompt[*i] != quote)
	{
		(*i)++;
		count++;
	}
	if (prompt[*i] == quote)
	{
		(*i)++;
		count++;
	}
	return (count);
}

static int	find_all_cmds_len(char *prompt, t_parsing *parsing)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (prompt[i])
	{
		while (ft_isspace(prompt[i]))
			i++;
		if (prompt[i] == '<' || prompt[i] == '>')
			i = skip_io(prompt, i, parsing);
		len++;
		while (prompt[i] && !ft_isspace(prompt[i])
			&& prompt[i] != '<' && prompt[i] != '>')
		{
			if (prompt[i] == '\'' || prompt[i] == '\"')
				len += skip_quote_cmd(prompt, &i);
			else
			{
				i++;
				len++;
			}
		}
	}
	return (len);
}

char	*extract_current_cmd(char *prompt, int *i, int *j, char *clean_cmd)
{
	char	quote;

	while (prompt[*i] && !ft_isspace(prompt[*i])
		&& prompt[*i] != '<' && prompt[*i] != '>')
	{
		if (prompt[*i] == '\'' || prompt[*i] == '\"')
		{
			quote = prompt[*i];
			clean_cmd[(*j)++] = prompt[(*i)++];
			while (prompt[*i] != quote)
				clean_cmd[(*j)++] = prompt[(*i)++];
			if (prompt[*i] == quote)
				clean_cmd[(*j)++] = prompt[(*i)++];
		}
		else if (prompt[*i])
			clean_cmd[(*j)++] = prompt[(*i)++];
	}
	return (clean_cmd);
}

char	*extract_clean_cmd(t_parsing *parsing, char *prompt)
{
	char	*clean_cmd;

	clean_cmd = malloc(sizeof(char) * (find_all_cmds_len(prompt, parsing) + 1));
	if (!clean_cmd)
		return (pars_err_char(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL));
	find_all_cmds(clean_cmd, prompt, parsing);
	return (clean_cmd);
}
