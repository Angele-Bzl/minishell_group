/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:55:46 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 12:55:47 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <signal.h>

static int	manage_signal_pid(int status)
{
	if (WTERMSIG(status) == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (WTERMSIG(status) == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	return (128 + WTERMSIG(status));
}

int	wait_for_pid(t_token *token, pid_t *pid)
{
	size_t	i;
	int		status;
	int		exit_status;
	t_token	*current;

	i = 0;
	exit_status = EXIT_OK;
	current = token;
	while (current)
	{
		if (waitpid(pid[i++], &status, 0) == -1)
		{
			if (errno == EINTR)
				continue ;
			set_signals_on(PROMPT_MODE);
			return (perror_return("waitpid", ERR));
		}
		if (WIFSIGNALED(status))
			exit_status = manage_signal_pid(status);
		else if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		current = current->next;
	}
	set_signals_on(PROMPT_MODE);
	return (exit_status);
}
