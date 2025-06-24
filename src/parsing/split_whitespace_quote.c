# include "minishell.h"

static int	get_next_word_bounds(const char *s, char c, int *start, int *end)
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

static int	free_split_on_failure(t_parsing *parsing, char **array, int limit)
{
	if (!array[limit])
	{
		while (limit + 1 > 0)
		{
			free(array[limit]);
			limit--;
		}
		free(array);
		parsing->errcode = ERR_MALLOC;
		return (-1);
	}
	return (0);
}

static int	fill_split_array(char **array, char const *s, char c, t_parsing *parsing)
{
	int		start;
	int		end;
	int		i;

	i = 0;
	end = 0;
	while (i < ft_countword(s, c))
	{
		if (get_next_word_bounds(s, c, &start, &end))
			return (0);
		array[i] = ft_substr(s, start, (end - start));
		if (array[i] == NULL)
		{
			parsing->errcode = ERR_MALLOC;
			return (-1);
		}
		array[i] = extract_token_without_quotes(array[i], parsing);
		if (array[i] == NULL)
			return (-1);
		if (free_split_on_failure(parsing, array, i) == -1)
			return (-1);
		i++;
	}
	array[i] = NULL;
	return (0);
}

char	**split_whitespace_quotes(char const *s, char c, t_parsing *parsing)
{
	int		word;
	char	**array;

	word = ft_countword(s, c);
	array = malloc(sizeof(char *) * (word + 1));
	if (!array)
	{
		parsing->errcode = ERR_MALLOC;
		return (NULL);
	}
	if (fill_split_array(array, s, c, parsing) == -1)
		return (NULL);
	return (array);
}
