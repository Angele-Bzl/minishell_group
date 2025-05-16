# include "minishell.h"

static int		next_pipe_segment(const char *s, char c, size_t *start, size_t *end);
static int		ft_countpipe(char const *s, char c);
static int		ft_free(char **array, size_t limit);

char	**pipe_segmentation(char const *s, char c)
{
	size_t	start;
	size_t	end;
	int		limit;
	int		word;
	char	**array;
	int		next_pipe_result;

	limit = 0;
	end = 0;
	word = ft_countpipe(s, c);
	if (word == -1)
		return(NULL);
	array = malloc(sizeof(char *) * (word + 1));
	if (!array)
		return (NULL);
	while (limit < word)
	{
		next_pipe_result = next_pipe_segment(s, c, &start, &end);
		if (next_pipe_result == 1)
			return (array);
		if (next_pipe_result == -1)
			return (NULL);
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

static int	next_pipe_segment(const char *s, char c, size_t *start, size_t *end)
{
	int	pipe_count;

	pipe_count = 0;
	*start = *end;
	while (s[*start] == c || s[*start] == ' ')
	{
		if (s[*start] == c)
			pipe_count++;
		*start = *start + 1;
		if (pipe_count > 1) // s'il y a plusieurs pipe sans rien entre les 2
		{
			printf("syntaxe error\n");
			return (-1);
		}
	}
	if (s[*start] == '\0' )
		return (1);
	*end = *start;
	while (s[*end] != c && s[*end] != '\0')
	{
		if (s[*end] == '\"' || s[*end] == '\'')
			*end = skip_under_quote(s, *end); // si s[i] = quote, on continue jusqu'a la prochaine
		*end = *end + 1;
	}
	return (0);
}

static int		ft_countpipe(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] == ' ') // on supprime les premiers espaces
		i++;
	if (s[i] == '|') // si on croise direct un pipe, syntax error
	{
		printf("syntaxe error\n");
		return (-1);
	}
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			i = skip_under_quote(s, i); // si s[i] = quote, on continue jusqu'a la prochaine
		while (s[i] == ' ')
			i++;
		if (s[i] == '\0')
			return (count);
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == '\"' || s[i] == '\'')
				i = skip_under_quote(s, i); // si s[i] = quote, on continue jusqu'a la prochaine
			i++;
		}
		count++;
		if (s[i] != '\0')
			i++;
	}
	return (count);
}
