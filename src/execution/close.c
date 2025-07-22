/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:55:08 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 12:55:09 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all(int fd0, int fd1)
{
	if (!(fd0 == STDIN_FILENO || fd0 == STDOUT_FILENO || fd0 == -1))
		close(fd0);
	if (!(fd1 == STDIN_FILENO || fd1 == STDOUT_FILENO || fd1 == -1))
		close(fd1);
}

void	close_free_token_env_pids(t_data *data, int fd0, int fd1, pid_t *pids)
{
	free_token_env(data);
	close_all(fd0, fd1);
	free(pids);
}

void	close_free_array_str(int fd0, int fd1, char **env, char *path)
{
	close_all(fd0, fd1);
	if (env)
		free_array(env);
	if (path)
		free(path);
}

int	close_all_return(int fd0, int fd1, int return_value)
{
	close_all(fd0, fd1);
	return (return_value);
}
