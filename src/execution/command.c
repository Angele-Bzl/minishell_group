/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:55:16 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 12:55:17 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	init_hyp_path(char **hyp_path, char *cmd, char **env_path)
{
	char	*path_w_backslash;
	size_t	i;

	i = 0;
	while (env_path[i])
	{
		path_w_backslash = ft_strjoin(env_path[i], "/");
		if (!path_w_backslash)
		{
			free_array(hyp_path);
			return (ERR);
		}
		hyp_path[i] = ft_strjoin(path_w_backslash, cmd);
		if (!hyp_path[i])
		{
			free(path_w_backslash);
			free_array(hyp_path);
			return (ERR);
		}
		free(path_w_backslash);
		i++;
	}
	return (OK);
}

static char	*return_err_cmd_malloc(char **env_path)
{
	free_array(env_path);
	return (msg_return_str(MALLOC, NULL, NULL));
}

static char	**hypothetical_path(char **env_path, char *cmd)
{
	char	**hypothetical_path_cmd;

	hypothetical_path_cmd = malloc(sizeof (char *) * tablen(env_path));
	if (!hypothetical_path_cmd)
		return (NULL);
	fill_tab_null(hypothetical_path_cmd, tablen(env_path));
	if (init_hyp_path(hypothetical_path_cmd, cmd, env_path) == ERR)
		return (NULL);
	return (hypothetical_path_cmd);
}

static char	*return_found_cmd(char *path_cmd, char *cmd, t_data *data)
{
	if (!path_cmd || !cmd[0])
	{
		if (path_cmd)
			free(path_cmd);
		data->exit_status = EXIT_CMD_NOT_FOUND;
		return (msg_return_str(NO_CMD, cmd, NULL));
	}
	return (path_cmd);
}

char	*find_cmd(char **env, char *cmd, t_data *data)
{
	char	**env_path;
	char	**hypothetical_path_cmd;
	char	*path_cmd;
	int		i;

	path_cmd = NULL;
	if (is_special_cmd(cmd, &path_cmd, data) == OK)
		return (path_cmd);
	i = find_path_in_env(env);
	if (i == ERR)
		return (msg_return_str(NO_FILE, cmd, NULL));
	env_path = ft_split(env[i], ':');
	if (!env_path)
		return (msg_return_str(MALLOC, NULL, NULL));
	env_path[0] = ft_strtrim_improved(env_path[0], "PATH=");
	if (!env_path[0])
		return_err_cmd_malloc(env_path);
	hypothetical_path_cmd = hypothetical_path(env_path, cmd);
	if (hypothetical_path_cmd == NULL)
		return_err_cmd_malloc(env_path);
	path_cmd = check_if_cmd_exists(hypothetical_path_cmd, env_path);
	free_array(env_path);
	return (return_found_cmd(path_cmd, cmd, data));
}
