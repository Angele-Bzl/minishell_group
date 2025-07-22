/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:36:48 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 15:36:49 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_exit(char *message, char *arg, int exit_value)
{
	char	*msg;

	if (message)
	{
		msg = ft_strjoin(arg, message);
		if (!msg)
		{
			ft_putstr_fd(MALLOC, STDERR_FILENO);
			exit(2);
		}
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	exit(exit_value);
}

int	msg_return(char *message, char *arg, int return_value)
{
	char	*msg;

	if (message)
	{
		msg = ft_strjoin(arg, message);
		if (!msg)
		{
			ft_putstr_fd(MALLOC, STDERR_FILENO);
			return (ERROR_SYSTEM);
		}
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	return (return_value);
}

char	*msg_return_str(char *message, char *arg, char *return_value)
{
	char	*msg;

	if (message)
	{
		msg = ft_strjoin(arg, message);
		if (!msg)
		{
			ft_putstr_fd(MALLOC, STDERR_FILENO);
			return (NULL);
		}
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	return (return_value);
}

int	perror_return(char *message, int return_value)
{
	if (message)
		perror(message);
	return (return_value);
}

void	end_single_cmd(t_data *data, int *io_fd, int *save, int return_val)
{
	close_all(io_fd[0], io_fd[1]);
	close_all(save[0], save[1]);
	if (return_val == EXIT_SYSTEM)
	{
		free_token_env(data);
		exit(STDERR_FILENO);
	}
	return ;
}
