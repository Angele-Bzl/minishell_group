#include "minishell.h"

int	execution(t_data *data)
{
	pid_t	*pids;

	if (!data->ls_token->cmd || !data->ls_token->cmd[0])
		return (OK);
	if (!data->ls_token->next && cmd_is_builtin(data->ls_token->cmd[0]))
		return (exec_single_cmd(data));
	pids = malloc(sizeof(pid_t) * count_cmds(data->ls_token));
	if (!pids)
		msg_exit(MALLOC, STDERR_FILENO, EXIT_FAILURE);
	// current = head;
	if (loop_children(data, pids) == ERR)
		return (ERR);
	wait_for_pid(data->ls_token, pids);
	return (OK);
}
