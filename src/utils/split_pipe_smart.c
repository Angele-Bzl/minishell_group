#include "../../header/minishell.h"

static int		ft_mark(const char *s, char c, size_t *start, size_t *end);
static size_t	ft_countword(char const *s, char c);
static int		ft_free(char **array, size_t limit);

char	**split_pipe_smart(char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	limit;
	size_t	word;
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

static int	ft_free(char **array, size_t limit)
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

static int	ft_mark(const char *s, char c, size_t *start, size_t *end)
{
	int	pipe_count;

	pipe_count = 0;
	*start = *end;
	while (s[*start] == c || s[*start] == ' ')
	{
		*start = *start + 1;
		pipe_count++;
		if (pipe_count > 1) // s'il y a plusieurs pipe sans rien entre les 2
		{
			// fail
		}
	}
	if (s[*start] == '\0' )
		return (1);
	*end = *start;
	while (s[*end] != c && s[*end] != '\0')
	{
		*end = skip_under_quote(s, *end); // si s[i] = quote, on continue jusqu'a la prochaine
		*end = *end + 1;
	}
	return (0);
}

static size_t	ft_countword(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] == ' ') // on supprime les premiers espaces
		i++;
	if (s[i] == '|') // si on croise direct un pipe, syntax error
	{
		// fail.
	}
	while (s[i])
	{
		i = skip_under_quote(s, i); // si s[i] = quote, on continue jusqu'a la prochaine
		if (s[i] == '\0')
			return (count);
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
	}
	return (count);
}
