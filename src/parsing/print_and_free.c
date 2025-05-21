# include "minishell.h"

void	print_and_free(char *str, t_data *data, t_parsing *parsing)
{
	if (str != NULL)			// si une str existe, la print
		printf("%s", str);
	free_all(data, parsing);	// it's free time
}
