#include "minishell.h"
#include <sys/stat.h>

static int	update_path_return(char **path_cmd, char *cmd, int return_value)
{
	*path_cmd = cmd;
	return (return_value);
}

int	is_special_cmd(char *cmd, char **path_cmd, t_data *data)
{
	struct stat	buf;

	if (!cmd || cmd_is_builtin(cmd))
		return (update_path_return(path_cmd, cmd, OK));
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &buf) == ERR)
		{
			data->exit_status = EXIT_CMD_NOT_FOUND;
			return (perror_return(cmd, OK));
		}
		else
		{
			if (S_ISDIR(buf.st_mode))
			{
				data->exit_status = EXIT_CMD_NO_PERMISSION;
				return (msg_return(IS_DIR, cmd, OK));
			}
			return (update_path_return(path_cmd, cmd, OK));
		}
	}
	return (1);
}

char	*check_if_cmd_exists(char **hypothetical_path_cmd, char **path)
{
	size_t	i;
	char	*real_path;
	bool	found;

	i = 0;
	found = false;
	real_path = NULL;
	while (path[i])
	{
		if (!access(hypothetical_path_cmd[i], X_OK) && !found)
		{
			real_path = ft_strdup(hypothetical_path_cmd[i]);
			found = true;
		}
		free(hypothetical_path_cmd[i]);
		i++;
	}
	free(hypothetical_path_cmd);
	hypothetical_path_cmd = NULL;
	return (real_path);
}
