#include "../../header/minishell.h"

char	**manage_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i] != "\"" || str[i] != "\'")
		i++;
	// tant que je ne croise pas de pipe et que prompt[i] != NULL, on incremente i.
	// Puis on "append" l'entrée du user à partir de là ou on s'est arreté.
	// 2 lignes pour une fonction si complexe, MDR.
	return (str);
}
