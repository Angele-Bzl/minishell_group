# include "minishell.h"

int	expand_var(t_data *data, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->prompt[i])
	{
		if (parsing->prompt[i] == '$')
			manage_dollar(data, parsing);
		i++;
	}
}