# include "minishell.h"

int	find_var_end(t_parsing *parsing)
{
	int	end;

	end = parsing->p_index;
	while (parsing->prompt[end] != ' ' || parsing->prompt[end] != '\'' || parsing->prompt[end] != ' \"'
		|| parsing->prompt[end] != '$')
		end++;
	return (end);
}

char *find_variable_content(char *new_word, t_data *data)
{
	char	*var;
	char	*result;
	char	*env_var;
	int		var_len;

	var = ft_strtrim(new_word, "$");
	if (!var)
		return (NULL); //fail malloc
	free(new_word);
	var_len = (ft_strlen(var));
	while (data->ls_env->next)
	{
		if (!ft_strncmp(data->ls_env->line, var, var_len) && data->ls_env->line[var_len + 1] == '=')
			env_var = data->ls_env->line;
		data->ls_env = data->ls_env->next;
	}
	if (!env_var)
		return (NULL); //si la variable existe pas c'est = NULL mais c'est pas un fail
	result = ft_cutstr(env_var, ft_strlen(var) + 1);
	if (!result)
		return (NULL); //fail malloc
	free(var);
	return (result);
}

char	*prompt_with_content(char *content, int start, t_data *data, t_parsing *parsing)
{
	int		i;
	int		j;
	int		end;
	int		prompt_len;
	char	*new_prompt;

	end = find_var_end(parsing);
	prompt_len = ft_strlen(parsing->prompt);
	prompt_len = prompt_len - (end - start) + (ft_strlen(content));
	new_prompt = malloc(sizeof(prompt_len) + 1);
	if (!new_prompt)
		return (NULL);
	i = 0;
	j = 0;
	while(parsing->prompt[i])
	{
		if (parsing->prompt[i] = '$')
		{
			while(content[j])
				new_prompt[i] = content[j];
			j = i;
			i = end;
		}
		if (j != 0)
		{
			new_prompt[j] = parsing->prompt[i];
			j++;
		}
		else
			new_prompt[i] = parsing->prompt[i];
		i++;
	}
}

void manage_dollar(t_data *data,t_parsing *parsing)
{
	char	*content;
	char	*old_prompt;
	char	*new_prompt;
	int		start;

	if (parsing->prompt[parsing->p_index] == '?')
	{
		// handle '?'
	}
	content = find_variable_content(data, parsing); // trouver le contenue de la variable, check fail
	old_prompt = parsing->prompt;
	start = parsing->p_index;
	parsing->prompt = NULL;
	new_prompt = prompt_with_content(content, start, data, parsing); // retirer la variable et rajouter contenu
}
