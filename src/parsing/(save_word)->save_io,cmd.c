#include "../../header/minishell.h"

//enregistrer le mot qu'on vient de lire et passer au mot suivant dans le char **cmds
// on lui envoie l'index et la taille du mot
// il supprime les operateurs superflus // fait en amont (pas tous)
//il remplace les variable par le mot litteral// reinitialise les booleens et word_length
// check si le mot est un file ou une cmd/arg

static char	*substr_no_quotes(char *prompt_line, int start, int new_len, int len, char skip)
{ //LA LEN EST PAS TOUT A FAIT BONNE POUR PARCOURIR PROMPTLINE
	char	*result;
	int	i;
	int p_line_len;

	p_line_len = (int)ft_strlen(prompt_line);
	if (start > p_line_len)
		len = 0;
	else if (len > (p_line_len - start))
		len = p_line_len - start;
	result = malloc(new_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len && (start + i < p_line_len)) // a optimiser
	{
		if (prompt_line[start + i] == '\\' && (prompt_line[start + i + 1] == skip || prompt_line[start + i + 1] == '\\'))
		{ // si on tombe sur un \, alors on check si le suivant est une quote ou un autre \. sinon on s'en fiche
			i++;
			result[i] = prompt_line[start + i];
		}
		else if (prompt_line[start + i] != skip)
			result[i] = prompt_line[start + i]; //si on s'en fiche on ecrit le char normal
		i++;
	}
	result[i] = '\0';
	return (result);
}

int save_word_in_tab(char *new_word, t_data *data, t_is_active *booleans)
{
	t_token_cmds    *new_token_cmd;

	new_token_cmd = malloc(sizeof(t_token_cmds));
	if (!new_token_cmd)
		return (0);
	/*SI C'EST UN FILE*/
	/*enregistrer si on doit effacer ou concatener ou ouvrir un here_doc*/
	if (booleans->double_left_rafter)
		data->ls_io->rafters[0] = DOUBLE_LEFT;
	else if (booleans->simple_left_rafter)
		data->ls_io->rafters[0] = SIMPLE_LEFT;
	if (booleans->double_right_rafter)
		data->ls_io->rafters[1] = DOUBLE_RIGHT;
	else if (booleans->simple_right_rafter)
		data->ls_io->rafters[1] = SIMPLE_RIGHT;
	/*enregistrer le file en input ou output*/
	if (data->ls_io->rafters[0] != NO_RAFTERS)
		data->ls_io->io[0] = new_word;
	if (data->ls_io->rafters[1] != NO_RAFTERS)
		data->ls_io->io[1] = new_word;
	/*SI C'EST PAS UN FILE*/
	if (data->ls_io->rafters[0] == NO_RAFTERS && data->ls_io->rafters[1] == NO_RAFTERS)
	{
		printf("(save word)hello\n");
		new_token_cmd->token_cmd = new_word; 
		new_token_cmd->next = NULL;
		data->ls_cmds = (t_cmds*)ft_lstlast((t_list*)data->ls_cmds); //
		ft_lstadd_back((t_list**)&data->ls_cmds->s_token_cmds, (t_list*)new_token_cmd);
	}
	return (1);
}


char	*find_var_in_env(t_env *env, char *var, int var_len)
{
	while (env->next)
	{
		if (!ft_strncmp(env->env_line, var, var_len) && env->env_line[var_len + 1] == '=')
			return (env->env_line);
		env = env->next;
	}
	return (NULL);
}

char *replace_variable(char *new_word, t_data *data)
{
	char	*var;
	char	*result;
	char	*env_var;

	var = ft_strtrim(new_word, "$");
	if (!var)
		return (NULL); //fail malloc
	free(new_word);

	env_var = find_var_in_env(data->ls_env, var, ft_strlen(var));
	if (!env_var)
		return (NULL); //si la variable existe pas c'est = NULL mais c'est pas un fail
	result = ft_cutstr(env_var, ft_strlen(var) + 1);
	if (!result)
		return (NULL); //fail malloc
	free(var);
	return (result);
}

int save_word(int *word_length, char *prompt_line, int *i, t_data *data, t_is_active *booleans)
{
	char    *new_word;
	int     index;
	char	skip;
	int     start;
	int		new_wl;

	new_wl = *word_length;
	skip = '\0';
	index = *i - *word_length;
	start = index;
	// printf("(save word) word length = %d\n", *word_length);
	if (*word_length == 0)
		return (0);
	while (index <= *i)
	{
		if (prompt_line[index] == '\"' && !booleans->simple_quote)
		{
			if (!booleans->double_quote)
			booleans->double_quote = true;
			else
			booleans->double_quote = false;
			new_wl--;
			skip = '\"';
		}
		if (prompt_line[index] == '\'' && !booleans->double_quote)
		{
			if (!booleans->simple_quote)
			booleans->simple_quote = true;
			else
			booleans->simple_quote = false;
			new_wl--;
			skip = '\'';
		}
		if (prompt_line[index] == '\\' && (prompt_line[index + 1] == '\\' || prompt_line[index + 1] == skip))
			new_wl--; // CE CAS N'EST PAS A GERER. "echo hello\ wolrd" devrais renvoyer "hello\ world".
		index++;
	}
	new_word = substr_no_quotes(prompt_line, start, new_wl, *word_length, skip);
	if (!new_word)
		return (0);
	if (booleans->dollar)
		new_word = replace_variable(new_word, data);
	save_word_in_tab(new_word, data, booleans);
	// printf("(save_word)mot actuel rangé : %s\n", data->ls_cmds->s_token_cmds->token_cmd);
	init_back_bool(booleans);
	*word_length = 0;
	return (0);
}
