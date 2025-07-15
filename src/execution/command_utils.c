#include "minishell.h"
#include <sys/stat.h>

int	is_special_cmd(char *cmd, char **path_cmd)
{
	struct stat	buf;

	if (!cmd || cmd_is_builtin(cmd))
	{
		*path_cmd = cmd;
		return (OK);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &buf) == -1)
			return (perror_return(cmd, OK));
		else
		{
			if (S_ISDIR(buf.st_mode))
				return (msg_return(IS_DIR, cmd, OK));
			*path_cmd = cmd;
			return (OK);
		}
	}
	return (1);
}

char	*return_err_cmd_malloc(char **env_path)
{
	free_array(env_path);
	return (msg_return_str(MALLOC, NULL, NULL));
}
