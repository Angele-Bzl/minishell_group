# include "minishell.h"

static int  env_init(t_env **ls_env, char **env)
{
	unsigned int	i;
	t_env			*new_node;

	i = 0;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (0);
		new_node->line = ft_strdup(env[i]);
		if (!new_node->line)
			return (0);
		new_node->next = NULL;
		ft_lstadd_back((t_list**)ls_env, (t_list*)new_node);
		new_node = new_node->next;
		i++;
	}
	return (1);
}

int	struct_init(t_data *data, t_parsing *parsing, char **env)
{
	data->ls_token = malloc(sizeof(t_token)); //data init
	if (!data->ls_token)
	return (0);
	data->ls_token->next = NULL;
	data->ls_token->cmd = NULL;
	data->ls_token->io[0] = NULL;
	data->ls_token->io[1] = NULL;
	data->ls_token->redirection[0] = NULL;
	data->ls_token->redirection[1] = NULL;
	data->ls_env = NULL;
	data->pipe_nbr = 0;
	if (env_init(&data->ls_env, env) == 0)
		return (0);
	parsing->data = data; //parsing init
	parsing->dollar = false;
	parsing->double_quote = false;
	parsing->simple_quote = false;
	parsing->skip = 0;
	parsing->prompt = NULL;
	parsing->prompt_tab = NULL;
	parsing->p_index = 0;
	parsing->word_length = 0;
	return(1);
}
