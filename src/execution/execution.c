#include "minishell.h"

int	execution(t_data *data)
{
	pid_t	*pids;
	t_token	*head;
	t_token	*current;

	head = data->ls_token;
	if (!head->cmd || !head->cmd[0])
		return (OK);
	if (!head->next && cmd_is_builtin(head->cmd[0]))
		return (exec_single_cmd(data));
	pids = malloc(sizeof(pid_t) * count_cmds(head));
	if (!pids)
		msg_exit("Error: pids malloc", STDERR_FILENO, STDERR_FILENO);
	current = head;
	if (loop_children(data, current, pids) == ERR)
		return (ERR);
	data->ls_token = head;
	wait_for_pid(head, pids);
	return (OK);
}
