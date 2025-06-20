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
	{
		if (!exec_single_cmd(data))
			return (ERR);
		return (OK);
	}
	pids = malloc(sizeof(pid_t) * count_cmds(head));
	if (!pids)
		msg_return("Error: pids malloc", STDERR_FILENO, ERR);
	current = head;
	if (loop_children(data, current, pids) == ERR)
		return (ERR);
	data->ls_token = head;
	wait_for_pid(head, pids);
	return (OK);
}
/*------------------------------------------------------------------------*/

// /*parsing*/
// if (open(fd) == -1)
// {
// 	free_all_parsing(parsing);
// 	errormsg_close_free_exit(parsing->data, perror(file_name), NULL, ERR);
// }
// fais tes trucs
// free_all_parsing(parsing)
// return (OK);

// HELLO(jhgfds)
// {
// 	if (">    >")
// 	{
// 		free_all_parsing(parsing);
// 		errormsg_close_free_return(parsing->data, RAFTERSPACE, NULL, ERR);
// 	}
// 	fais tes trucs
// 	free_all_parsing(parsing)
// 	return (OK);
// }

// if (HELLO(arguement) != OK)
// {
// 	return (ERR);
// }


// /*exec*/
// if (open(fd) == -1)
// {
// 	errormsg_close_free_exit(data, perror(file_name), fd, ERR);
// }
// fais tes trucs
// errormsg_close_free_exit(data, NULL, NULL, OK)


// free_all_parsing(parsing)
// {
// 	free(parsing->prout);
// 	free(parsing->prout1);
// 	free(parsing->prout2);
// }

// errormsg_close_free_exit(t_data *data, char *errormsg, void *argument, int exitcode)
// {
// 	if (errormsg)
// 		ft_printf_err(errormsg, argument);
// 	close_all(data->fd);
// 	free_all(data->trucafree);
// 	exit(exitcode);
// }
// errormsg_close_free_return(t_data *data, char *errormsg, void *argument, int exitcode)
// {
// 	if (errormsg)
// 		ft_printf_err(errormsg, argument);
// 	close_all(data->fd);
// 	free_all(data->trucafree);
// 	return(exitcode);
// }
