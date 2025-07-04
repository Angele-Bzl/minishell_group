#include "minishell.h"

char	*extract_token_without_quotes(char *str, t_parsing *parsing)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
	{
		parsing->errcode = ERR_MALLOC;
		return (NULL);
	}
	while (str[i])
	{
		quote_check(str[i], parsing);
		if (str[i] == '\'' && parsing->double_quote == false)
			i++;
		else if (str[i] == '\"' && parsing->simple_quote == false)
			i++;
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
