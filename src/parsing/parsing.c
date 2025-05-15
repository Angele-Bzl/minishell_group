#include "../../header/minishell.h"

void second_parsing(t_data *data, t_parsing *parsing)
{
	while (parsing->prompt[parsing->p_index])
	{
		if (parsing->prompt[parsing->p_index] == '\'')
			manage_simple_quote();
			// boolen = true ou false 
		else if (parsing->prompt[parsing->p_index] == '\"')
			manage_double_quote(prompt_line, &i, &booleans, data, &word_length);
			// boolen = true ou false
		else if (parsing->prompt[parsing->p_index] == '|') 
			manage_pipe(prompt_line, &i, &booleans, data, &word_length); 
			//termine le node actuel, crée un nouveau node, met a jour le input et le output suivant (pipe)
		else if (parsing->prompt[parsing->p_index] == '>')
			manage_right_rafter(prompt_line, &i, &booleans, data, &word_length);
			//bool pour savoir si c'est > ou >> SINON error syntax. chercher ' ' ou ' " ' suivant pour delimiter le fd outfile
		else if (parsing->prompt[parsing->p_index] == '<')
			manage_left_rafter(prompt_line, &i, &booleans, data, &word_length);
			//bool pour savoir si c'est > ou >> SINON error syntax. chercher ' ' ou ' " ' suivant pour delimiter le fd infile
		else if (parsing->prompt[parsing->p_index] == '$')
			manage_dollar(prompt_line, &booleans, data, &i, &word_length); 
			//si simple quote : RIEN, sinon chercher ' ' ou ' " ' suivant pour delimiter la $VAR
		else if (ft_isspace(prompt_line[i]) && !booleans.simple_quote && !booleans.double_quote)
			save_word(&word_length, prompt_line, &i, data, &booleans);
			//enregistrer le mot qu'on vient de lire et passer au mot suivant dans le char **cmds
		else
			word_length++;
		i++;
	}
	printf("(parsing)word length = %d\n", word_length);
	save_word(&word_length, prompt_line, &i, data, &booleans); //save le dernier mot
	printf("(parsing)mot actuel rangé : %s\n", data->ls_cmds->s_token_cmds->token_cmd);
}

int	parser(t_data *data, t_parsing *parsing)
{
	int	i;
	
	handle_eardoc(data, parsing);
	i = 0;
	while(parsing->prompt[i])
	{
		if (parsing->prompt[i] == '|')
			data->pipe_nbr++;
		i++;
	}
	manage_dollar(data, parsing); // à faire dans l'execution ?
}
