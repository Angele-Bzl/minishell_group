#include "minishell.h"

char	*ft_cutstr(char const *s, unsigned int start)
{
	char		*result;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(s) - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
