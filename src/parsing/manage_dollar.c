# include "minishell.h"

char *find_var_content(char *variable, t_data *data, int *errcode)
{
	char	*var;
	char	*result;
	char	*env_var;
	int		var_len;
	t_env	*tmp;

	env_var = NULL;
	tmp = data->ls_env;
	var = ft_strtrim(variable, "$");
	if (!var)
	{
		*errcode = ERR_MALLOC;
		return (NULL); 											//fail malloc
	}
	free(variable);
	var_len = (ft_strlen(var));
	env_var = search_and_fill_content_with_env(tmp, var, var_len);
	result = ft_cutstr(env_var, ft_strlen(var) + 1);
	if (!result)
	{
		*errcode = ERR_MALLOC;
		return (NULL); 											//fail malloc
	}
	free(var);
	return (result);
}

static char	*prompt_with_content(char *content, int start, t_parsing *parsing)
{
	int		i;
	int		j;
	int		end;
	int		prompt_len;
	char	*new_prompt;

	end = find_var_end(parsing->old_prompt, parsing->p_index);
	prompt_len = ft_strlen(parsing->old_prompt) - (end - start) + (ft_strlen(content));
	new_prompt = malloc(sizeof(char) * (prompt_len + 1));
	if (!new_prompt)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)												// copier ce qui se trouve avant la variable.
		new_prompt[j++] = parsing->old_prompt[i++];
	while (content && content[j - i])								// inserer valeur de la variable.
	{
		new_prompt[j] = content[j - i];								// j - i car on veut content[0].
		j++;
	}
	i = end;
	while (parsing->old_prompt[i]) 												// recopier la fin du prompt
		new_prompt[j++] = parsing->old_prompt[i++];
	new_prompt[j] = '\0';
	return (new_prompt);
}

static int	init_variable_and_content(t_parsing *parsing, char **variable, char **content, int *errcode)
{
	*variable = find_var_name(parsing);
	if (!*variable)
		return (ERR_MALLOC);
	*content = find_var_content(*variable, parsing->data, errcode); 					// trouver le contenue de la variable, check fail
	if (!*content)																		// on continue en remplaçant par rien
	{
		*content = malloc(1);
		if (!*content)
			return (ERR_MALLOC); 														// fail malloc
		*content[0] = '\0';
	}
	return (*errcode);
}

int	fill_new_prompt(t_parsing *parsing, char *content)
{
	int	start;

	start = parsing->p_index;
	parsing->old_prompt = parsing->prompt_tab[parsing->pipe_seg];
	parsing->prompt_tab[parsing->pipe_seg] = NULL;
	parsing->prompt_tab[parsing->pipe_seg] = prompt_with_content(content, start, parsing);	// retirer la variable et rajouter contenu
	if (!parsing->prompt_tab[parsing->pipe_seg])
		return (ERR_MALLOC);
	parsing->p_index = start + ft_strlen(content);
	return (OK);
}

int manage_dollar_sign(t_parsing *parsing, int *errcode)
{
	char	*content;
	char	*variable;

	(void)errcode;
	if (parsing->prompt_tab[parsing->pipe_seg][parsing->p_index] == '?')
	{
		// handle '?'
	}
	*errcode = init_variable_and_content(parsing, &variable, &content, errcode);
	if (errcode == OK)
		*errcode = fill_new_prompt(parsing, content);
	return (*errcode);
}
