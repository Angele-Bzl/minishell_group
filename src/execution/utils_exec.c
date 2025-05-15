# include "minishell.h"

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

char	*free_tab(char **table)
{
	int	i;

	i = 0;
	if (table && table[i])
	{
		free(table[i]);
		table[i] = NULL;
	}
	i++;
	while (table && table[i])
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	if (table)
	{
		free(table);
		table = NULL;
	}
	return (NULL);
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
	int	i;
	int	status;

	i = 0;
	while (token)
	{
		if (waitpid(pid[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		i++;
		token = token->next;
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
	int		i;

	table_env = malloc(sizeof(char*) * ft_lstsize((t_list*)&node_env));
	if (!table_env)
		return (NULL);
	i = 0;
	while (node_env)
	{
		table_env[i] = ft_strdup(node_env->line);
		if (!table_env[i])
		{
			free_tab(table_env);
			return (NULL);
		}
		node_env = node_env->next;
		i++;
	}
	return (table_env);
}
