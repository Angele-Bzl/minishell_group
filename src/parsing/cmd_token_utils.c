# include "minishell.h"

static int		ft_mark(const char *s, char c, int *start, int *end);
static int	ft_countword(char const *s, char c);
static int		ft_free(char **array, int limit);

char	**split_whitespace_quotes(char const *s, char c)
{
	int	start;
	int	end;
	int	limit;
	int	word;
	char	**array;

	limit = 0;
	end = 0;
	word = ft_countword(s, c);
	array = malloc(sizeof(char *) * (word + 1));
	if (!array)
		return (NULL);
	while (limit < word)
	{
		if (ft_mark(s, c, &start, &end))
			return (array);
		array[limit] = ft_substr(s, start, (end - start));
		if (ft_free(array, limit))
			return (NULL);
		limit++;
	}
	array[limit] = NULL;
	return (array);
}

static int	ft_free(char **array, int limit)
{
	if (!array[limit])
	{
		while (limit + 1 > 0)
		{
			free(array[limit]);
			limit--;
		}
		free(array);
		return (1);
	}
	return (0);
}

static int	ft_mark(const char *s, char c, int *start, int *end)
{
	*start = *end;
	while (s[*start] == c)
		(*start)++;
	if (s[*start] == '\0' )
		return (1);
	*end = *start;
	while (s[*end] && s[*end] != c)
	{
		if (s[*end] == '\'' || s[*end] == '\"')
			*end = skip_quote(s, end);
		else
			(*end)++;
	}
	return (0);
}

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break;
		count++;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '\"')
				i = skip_quote(s, &i);
			else
				i++;
		}
	}
	return (count);
}
