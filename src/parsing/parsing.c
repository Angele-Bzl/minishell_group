# include "minishell.h"

int	ft_parsing(t_data *data, t_parsing *parsing)
{
	int	i;

	i = 0;
	if (prompt_check(parsing->prompt, parsing) == -1)	// check si le prompt a des quotes ouverte ou finit par un pipe. Ne pas gerer les cas de heredoc
		return (ERR);
		//print_and_free("syntax error : heredoc not handled\n", data, parsing);
	parsing->prompt_tab = pipe_segmentation(parsing->prompt, '|'); // créer le prompt_tab et print les erreurs
	if (!parsing->prompt_tab)					// en cas de soucis, free sans print
		return (ERR);
	// print_prompt_tab(parsing->prompt_tab);
	if (expand_var(data, parsing) == -1)		// si mauvais, expand et on free
		return (ERR);
	// printf("\n----------- after expand -----------\n\n");
	// print_prompt_tab(parsing->prompt_tab);
	if (tokenisation(data, parsing) == -1)
		return (ERR);
	// 	print_and_free(NULL, data, parsing);	// gerer la cmd ou le i/o
	// print_tokens(data);
	return (0);
}
