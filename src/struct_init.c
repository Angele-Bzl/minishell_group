/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:32:51 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:32:52 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_no_env(t_env **current, t_data *data)
{
	t_env	*new_node;
	char	**cmds;

	new_node = malloc(sizeof (t_env));
	if (!new_node)
		return (msg_return(MALLOC, NULL, ERR));
	new_node->line = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!new_node->line)
	{
		free(new_node);
		return (msg_return(MALLOC, NULL, ERR));
	}
	new_node->next = NULL;
	ft_lstadd_back((t_list **)current, (t_list *)new_node);
	cmds = ft_split("export OLDPWD=", ' ');
	if (!cmds)
		return (msg_return(MALLOC, NULL, ERR));
	exec_export(*current, cmds, data);
	free_array(cmds);
	return (OK);
}

int	env_init(char **env, t_data *data)
{
	unsigned int	i;
	t_env			*new_node;

	data->ls_env = NULL;
	i = 0;
	if (!env || !env[0])
		return (manage_no_env(&data->ls_env, data));
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (msg_return(MALLOC, NULL, ERR));
		new_node->line = ft_strdup(env[i++]);
		if (!new_node->line)
		{
			free(new_node);
			free_env(data->ls_env);
			return (msg_return(MALLOC, NULL, ERR));
		}
		new_node->next = NULL;
		ft_lstadd_back((t_list **)&data->ls_env, (t_list *)new_node);
		new_node = new_node->next;
	}
	return (OK);
}

static int	data_init(t_data *data)
{
	data->ls_token = token_lstnew();
	if (!data->ls_token)
		return (ERR);
	data->pipe_nbr = 0;
	return (OK);
}

static void	parsing_init(t_data *data, t_parsing *parsing)
{
	parsing->data = data;
	parsing->errcode = ALL_OK;
	parsing->dollar = false;
	parsing->double_quote = false;
	parsing->simple_quote = false;
	parsing->outfile_issue = false;
	parsing->skip = 0;
	parsing->prompt = NULL;
	parsing->old_prompt = NULL;
	parsing->prompt_tab = NULL;
	parsing->pipe_seg = 0;
	parsing->p_index = 0;
	parsing->word_length = 0;
}

int	struct_init(t_data *data, t_parsing *parsing)
{
	if (data_init(data) == ERR)
		return (ERR);
	parsing_init(data, parsing);
	return (OK);
}
