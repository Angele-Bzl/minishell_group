# include "minishell.h"

int	find_var_end(char *prompt, int p_index)
{
	int	end;

	end = p_index + 1;
	while (prompt[end] != ' ' && prompt[end] != '\'' && prompt[end] != '\"'
		&& prompt[end] != '$' && prompt[end] != '\0')
		end++;
	return (end);
}

char *find_var_content(char *variable, t_data *data)
{
	char	*var;
	char	*result;
	char	*env_var;
	int		var_len;
	t_env	*tmp;

	env_var = NULL;
	tmp = data->env_head;
	var = ft_strtrim(variable, "$");
	if (!var)
		return (NULL); 											//fail malloc
	free(variable);
	var_len = (ft_strlen(var));
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, var, var_len) && tmp->line[var_len] == '=')
		{
			env_var = tmp->line;
			break;
		}
		tmp = tmp->next;
	}
	if (!env_var)
		return (NULL); 											//si la variable existe pas c'est = NULL mais c'est pas un fail
	result = ft_cutstr(env_var, ft_strlen(var) + 1);
	if (!result)
		return (NULL); 											//fail malloc
	free(var);
	return (result);
}

char	*prompt_with_content(char *content, int start, char *prompt, int p_index)
{
	int		i;
	int		j;
	int		end;
	int		prompt_len;
	char	*new_prompt;

	end = find_var_end(prompt, p_index);
	prompt_len = ft_strlen(prompt) - (end - start) + (ft_strlen(content));
	new_prompt = malloc(sizeof(char) * (prompt_len + 1));
	if (!new_prompt)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)												// copier ce qui se trouve avant la variable.
		new_prompt[j++] = prompt[i++];
	while (content && content[j - i])								// inserer valeur de la variable.
	{
		new_prompt[j] = content[j - i];								// j - i car on veut content[0].
		j++;
	}
	i = end;
	while (prompt[i]) 												// recopier la fin du prompt
		new_prompt[j++] = prompt[i++];
	new_prompt[j] = '\0';
	//printf("%s\n", new_prompt);
	return (new_prompt);
}

int manage_dollar(t_data *data,t_parsing *parsing)
{
	char	*content;
	char	*old_prompt;
	char	*variable;
	int		start;

	if (parsing->prompt_tab[parsing->pipe_seg][parsing->p_index] == '?')
	{
		// handle '?'
	}
	variable = find_var_name(parsing);
	content = find_var_content(variable, data); 					// trouver le contenue de la variable, check fail
	if (!content)													// on continue en remplaçant par rien
	{
		content = malloc(1);
		if (!content)
			return (-1); 											// fail malloc
		content[0] = '\0';
	}
	old_prompt = parsing->prompt_tab[parsing->pipe_seg];
	start = parsing->p_index;
	parsing->prompt_tab[parsing->pipe_seg] = NULL;
	parsing->prompt_tab[parsing->pipe_seg] = prompt_with_content(content, start,
			old_prompt, parsing->p_index);							// retirer la variable et rajouter contenu
	if (!parsing->prompt_tab[parsing->pipe_seg])
		return (-1);
	parsing->p_index = start + ft_strlen(content);
	return (0);
}
