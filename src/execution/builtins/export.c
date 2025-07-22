/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:54:41 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 12:54:42 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_is_valid(char *cmd)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(cmd[i]) || cmd[i] == '_'))
		return (msg_return(NOT_VALID_IDENTIFIER, cmd, false));
	i++;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (msg_return(NOT_VALID_IDENTIFIER, cmd, false));
		i++;
	}
	return (true);
}

static int	var_new(t_env *ls_env, char *cmd)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (msg_return(MALLOC, NULL, ERR));
	new->line = ft_strdup(cmd);
	if (!new->line)
		return (msg_return(MALLOC, NULL, ERR));
	new->next = NULL;
	ft_lstadd_back((t_list **)&ls_env, (t_list *)new);
	return (OK);
}

static int	var_already_exists(t_env *current, char *cmd)
{
	while (current)
	{
		if (var_cmp(current->line, cmd))
		{
			return (true);
		}
		current = current->next;
	}
	return (false);
}

static int	var_update(t_env *current, char *cmd)
{
	while (current)
	{
		if (var_cmp(current->line, cmd))
		{
			free(current->line);
			current->line = ft_strdup(cmd);
			if (!current->line)
				return (msg_return(MALLOC, NULL, ERR));
		}
		current = current->next;
	}
	return (OK);
}

int	exec_export(t_env *ls_env, char **cmds, t_data *data)
{
	int		i;
	t_env	*current;

	current = ls_env;
	i = 1;
	if (!cmds[i])
		exec_env_export(ls_env);
	while (cmds[i])
	{
		if (var_is_valid(cmds[i]))
		{
			if (var_already_exists(current, cmds[i]))
			{
				if (var_update(current, cmds[i]) == ERR)
					return (ERROR_SYSTEM);
			}
			else if (var_new(ls_env, cmds[i]) == ERR)
				return (ERROR_SYSTEM);
		}
		else
			data->exit_status = EXIT_PROMPT;
		i++;
	}
	return (OK);
}
