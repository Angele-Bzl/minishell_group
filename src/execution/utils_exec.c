#include "minishell.h"

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

int	tablen(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

int	wait_for_pid(t_token *token, pid_t *pid)
{
	int		i;
	int		status;
	t_token	*current;

	i = 0;
	status = 0;
	current = token;
	while (current)
	{
		if (waitpid(pid[i], &status, 0) == -1)
			return (perror_return("waitpid", ERR));
		i++;
		current = current->next;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

char	**get_env_in_tab(t_env *node_env)
{
	char	**table_env;
	t_env	*current;
	int		i;

	current = node_env;
	table_env = malloc(sizeof (char *) * (ft_lstsize((t_list *)current) + 1));
	if (!table_env)
		return (NULL);
	i = 0;
	while (current)
	{
		table_env[i] = ft_strdup(current->line);
		if (!table_env[i])
		{
			free_array(table_env);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	table_env[i] = NULL;
	return (table_env);
}

int	count_cmds(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}
