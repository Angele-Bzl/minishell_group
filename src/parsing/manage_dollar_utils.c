# include "minishell.h"

char	*find_var_name(t_parsing *parsing)
{
	int		i;
	int		start;
	int		end;
	int		var_len;
	char	*var_name;

	start = parsing->p_index;
	end = start;
	while (parsing->prompt[end] != ' ' && parsing->prompt[end] != '\'' && parsing->prompt[end] != '\"'
		&& parsing->prompt[end] != '$' && parsing->prompt[end] != '\0')
		end++;
	var_len = end - start;
	var_name = malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < var_len)
	{
		var_name[i] = parsing->prompt[start + i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}
