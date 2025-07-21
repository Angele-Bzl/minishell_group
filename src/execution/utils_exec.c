#include "minishell.h"
#include <errno.h>
#include <signal.h>

char	*ft_strtrim_improved(char *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*result;

	i = 0;
	start = -1;
	end = -2;
	while (s1[i] && start == -1)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			start = i;
		i++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0 && end == -2)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			end = i;
		i--;
	}
	result = ft_substr(s1, start, (end - start) + 1);
	free(s1);
	return (result);
}

size_t	tablen(char **table)
{
	size_t	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

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

char	**get_env_in_tab(t_env *node_env)
{
	char	**table_env;
	t_env	*current;
	size_t	i;

	current = node_env;
	table_env = malloc(sizeof (char *) * (ft_lstsize((t_list *)current) + 1));
	if (!table_env)
		return (NULL);
	i = 0;
	while (current)
	{
		if (ft_strchr(current->line, '='))
		{
			table_env[i] = ft_strdup(current->line);
			if (!table_env[i])
			{
				free_array(table_env);
				return (NULL);
			}
		}
		current = current->next;
		i++;
	}
	table_env[i] = NULL;
	return (table_env);
}

size_t	count_cmds(t_token *token)
{
	size_t	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}
