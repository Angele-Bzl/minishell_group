/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:55:43 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 12:55:44 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

char	*ft_strtrim_improved(char *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*result;

	i = 0;
	start = -1;
	end = -2;
	while (s1[i] && start == -1)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			start = i;
		i++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0 && end == -2)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			end = i;
		i--;
	}
	result = ft_substr(s1, start, (end - start) + 1);
	free(s1);
	return (result);
}

size_t	tablen(char **table)
{
	size_t	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

char	**get_env_in_tab(t_env *node_env)
{
	char	**table_env;
	t_env	*current;
	size_t	i;

	current = node_env;
	table_env = malloc(sizeof (char *) * (ft_lstsize((t_list *)current) + 1));
	if (!table_env)
		return (NULL);
	i = 0;
	while (current)
	{
		if (ft_strchr(current->line, '='))
		{
			table_env[i] = ft_strdup(current->line);
			if (!table_env[i])
			{
				free_array(table_env);
				return (NULL);
			}
		}
		current = current->next;
		i++;
	}
	table_env[i] = NULL;
	return (table_env);
}

size_t	count_cmds(t_token *token)
{
	size_t	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}
