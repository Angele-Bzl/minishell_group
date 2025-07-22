/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:55:34 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 12:55:35 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	exstat_per_ret(int *exstat, int exstat_val, char *msg, int ret_val)
{
	*exstat = exstat_val;
	return (perror_return(msg, ret_val));
}

static int	get_inpt_(t_file *ls_infile, int *save_std, int *ex_stat)
{
	int		input;
	t_file	*curr;

	save_std[0] = dup(STDIN_FILENO);
	if (save_std[0] == ERR)
		return (exstat_per_ret(ex_stat, EXIT_SYSTEM, "dup2", ERR));
	input = STDIN_FILENO;
	if (ls_infile->value)
	{
		curr = ls_infile;
		while (curr)
		{
			input = open(curr->value, O_RDONLY);
			if (input == -1)
				return (exstat_per_ret(ex_stat, EXIT_PROMPT, curr->value, ERR));
			if (curr->redirection == DOUBLE_LEFT)
				unlink(curr->value);
			if (curr->next)
				close(input);
			curr = curr->next;
		}
	}
	return (input);
}

static int	get_outpt_(t_file *ls_outf, int *save_std, int *ex_stat)
{
	int		output;
	t_file	*curr;

	save_std[1] = dup(STDOUT_FILENO);
	if (save_std[1] == ERR)
		return (exstat_per_ret(ex_stat, EXIT_SYSTEM, "dup2", ERR));
	output = STDOUT_FILENO;
	if (ls_outf->value)
	{
		curr = ls_outf;
		while (curr)
		{
			if (curr->redirection == SIMPLE_RIGHT)
				output = open(curr->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (curr->redirection == DOUBLE_RIGHT)
				output = open(curr->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (output == -1)
				return (exstat_per_ret(ex_stat, EXIT_PROMPT, curr->value, ERR));
			if (curr->next)
				close(output);
			curr = curr->next;
		}
	}
	return (output);
}

static int	reset_dup2(int *save_std_io)
{
	if (dup2(save_std_io[0], STDIN_FILENO) == -1)
		return (perror_return("dup2", ERR));
	if (dup2(save_std_io[1], STDOUT_FILENO) == -1)
		return (perror_return("dup2", ERR));
	close_all(save_std_io[0], save_std_io[1]);
	return (OK);
}

void	exec_single_builtin(t_data *dt)
{
	int		io_fd[2];
	int		save_std[2];

	io_fd[0] = get_inpt_(dt->ls_token->ls_infile, save_std, &dt->exit_status);
	if (io_fd[0] == ERR)
		return (end_single_cmd(dt, io_fd, save_std, dt->exit_status));
	io_fd[1] = get_outpt_(dt->ls_token->ls_outfile, save_std, &dt->exit_status);
	if (io_fd[1] == ERR)
		return (end_single_cmd(dt, io_fd, save_std, dt->exit_status));
	redir_exec(dt->ls_token, io_fd, dt, save_std);
	if (dt->exit_status != EXIT_OK)
		return (end_single_cmd(dt, io_fd, save_std, dt->exit_status));
	if (reset_dup2(save_std) == ERR)
		return (end_single_cmd(dt, io_fd, save_std, ERROR_SYSTEM));
	close_all(io_fd[0], io_fd[1]);
	return ;
}
