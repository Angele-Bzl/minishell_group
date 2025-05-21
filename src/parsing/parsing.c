# include "minishell.h"

// int	create_prompt_tab(t_data *data, t_parsing *parsing)
// {
// 	int	i;

// 	handle_eardoc(data, parsing);
// 	i = 0;
// 	while(parsing->prompt[i])
// 	{
// 		if (parsing->prompt[i] == '|')
// 			data->pipe_nbr++;
// 		i++;
// 	}
// 	manage_dollar(data, parsing); // à faire dans l'execution ?
// }

// void parse_current_pipe_segment(t_data *data, t_parsing *parsing)
// {
// 	while (parsing->prompt[parsing->p_index])
// 	{
// 		if (parsing->prompt[parsing->p_index] == '\'')
// 			manage_simple_quote();
// 			// boolen = true ou false
// 		else if (parsing->prompt[parsing->p_index] == '\"')
// 			manage_double_quote(prompt_line, &i, &booleans, data, &word_length);
// 			// boolen = true ou false
// 		else if (parsing->prompt[parsing->p_index] == '|')
// 			manage_pipe(prompt_line, &i, &booleans, data, &word_length);
// 			//termine le node actuel, crée un nouveau node, met a jour le input et le output suivant (pipe)
// 		else if (parsing->prompt[parsing->p_index] == '>')
// 			manage_right_rafter(prompt_line, &i, &booleans, data, &word_length);
// 			//bool pour savoir si c'est > ou >> SINON error syntax. chercher ' ' ou ' " ' suivant pour delimiter le fd outfile
// 		else if (parsing->prompt[parsing->p_index] == '<')
// 			manage_left_rafter(prompt_line, &i, &booleans, data, &word_length);
// 			//bool pour savoir si c'est > ou >> SINON error syntax. chercher ' ' ou ' " ' suivant pour delimiter le fd infile
// 		else if (parsing->prompt[parsing->p_index] == '$')
// 			manage_dollar(prompt_line, &booleans, data, &i, &word_length);
// 			//si simple quote : RIEN, sinon chercher ' ' ou ' " ' suivant pour delimiter la $VAR
// 		else if (ft_isspace(prompt_line[i]) && !booleans.simple_quote && !booleans.double_quote)
// 		{
// 			if ()
// 			save_word(&word_length, prompt_line, &i, data, &booleans);
// 	 		//enregistrer l'input/output ou la cmd et ses args
// 		}
// 		else
// 			word_length++;
// 		i++;
// 	}
// 	save_word(&word_length, prompt_line, &i, data, &booleans); //save le dernier mot
// }

int	ft_parsing(t_data *data, t_parsing *parsing)
{
	(void)data;
	int	i;

	i = 0;
	if (prompt_check(parsing->prompt) == -1)	// check si le prompt a des quotes ouverte ou finit par un pipe. Ne pas gerer les cas de heredoc
			print_and_free("sybrax error : heredoc not handled\n", data, parsing);
	parsing->prompt_tab = pipe_segmentation(parsing->prompt, '|'); // créer le prompt_tab et print les erreurs
	if (!parsing->prompt_tab)					// en cas de soucis, free sans print
		print_and_free(NULL, data, parsing);
	print_prompt_tab(parsing->prompt_tab); 
	if (expand_var(data, parsing) == -1)		// si mauvais, expand et on free
		print_and_free(NULL, data, parsing);
	print_prompt_tab(parsing->prompt_tab);
												// gerer la cmd ou le i/o
	return (0);
}
