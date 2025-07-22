/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:55:30 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 16:37:53 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>
#include <signal.h>

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_sigreceived = 1;
		rl_done = 1;
	}
}

static int	readline_heredoc(int fd, char *eof)
{
	char	*input;

	input = NULL;
	while (1)
	{
		rl_event_hook = takes_a_value;
		input = readline("> ");
		if (g_sigreceived)
		{
			g_sigreceived = 0;
			free(input);
			return (HEREDOC_INTERRUPTED);
		}
		if (!input)
			return (msg_return(HDOC_EXPECT_EOF, eof, OK));
		if (!ft_strncmp(input, eof, ft_strlen(eof)))
			break ;
		ft_putendl_fd(input, fd);
		free(input);
		input = NULL;
	}
	free(input);
	input = NULL;
	return (OK);
}

static int	change_tmp_name(char *tmp, int i)
{
	if (tmp[i] < 90)
		tmp[i] = tmp[i] + 1;
	else if (i > 0)
	{
		if (change_tmp_name(tmp, i - 1) == ERR)
			return (ERR);
	}
	else
		return (ERR);
	return (OK);
}

static char	*generate_name_tmp(void)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(".AAAAAAAAAA.tmp");
	if (!tmp)
		return (msg_return_str(MALLOC, NULL, NULL));
	while (1)
	{
		if (!access(tmp, F_OK))
		{
			i = 10;
			if (change_tmp_name(tmp, i) == ERR)
				return (msg_return_str(HEREDOC_NAME, NULL, NULL));
		}
		else
			return (tmp);
	}
}

char	*here_doc(char *eof, t_parsing *parsing)
{
	int		fd;
	int		ret;
	char	*tmp;

	tmp = generate_name_tmp();
	if (!tmp)
		return (free_return_str(eof, NULL));
	set_signals_on(HEREDOC_MODE);
	fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (free_return_str(eof, NULL));
	ret = readline_heredoc(fd, eof);
	free(eof);
	close (fd);
	if (ret == HEREDOC_INTERRUPTED)
	{
		parsing->errcode = ERR_PROMPT;
		parsing->data->exit_status = 130;
		unlink(tmp);
		return (free_return_str(tmp, NULL));
	}
	return (tmp);
}
