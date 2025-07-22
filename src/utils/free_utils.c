/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:32:10 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:32:11 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->line);
		env->line = NULL;
		free(env);
		env = NULL;
		env = tmp;
	}
}

static void	free_file(t_file *current)
{
	t_file	*next;

	while (current)
	{
		next = current->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
}

void	free_files(t_token *ls_token)
{
	t_file	*current;

	current = ls_token->ls_infile;
	free_file(current);
	current = ls_token->ls_outfile;
	free_file(current);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->cmd)
			free_array(token->cmd);
		if (token->ls_infile || token->ls_outfile)
			free_files(token);
		free(token);
		token = tmp;
	}
}
