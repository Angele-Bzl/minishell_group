#include "minishell.h"
#include <wait.h>

void	execution(t_data *data)
{
	pid_t	*pids;

	if (!data->ls_token->cmd[0])
		data->ls_token->cmd[0] = NULL;
	if (!data->ls_token->next && cmd_is_builtin(data->ls_token->cmd[0]))
		return (exec_single_builtin(data));
	pids = malloc(sizeof(pid_t) * count_cmds(data->ls_token));
	if (!pids)
		msg_exit(MALLOC, NULL, EXIT_FAILURE);
	if (loop_children(data, pids) == ERR)
	{
		data->exit_status = EXIT_SYSTEM;
		return ;
	}
	data->exit_status = wait_for_pid(data->ls_token, pids);
	if (data->exit_status == ERR)
	{
		free(pids);
		exit(EXIT_FAILURE);
	}
	free(pids);
	return ;
}
