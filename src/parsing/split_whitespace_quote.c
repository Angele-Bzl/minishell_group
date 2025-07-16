#include "minishell.h"

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
			break ;
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
		return (parsing_error_int(parsing, ERR_MALLOC, EXIT_SYSTEM, ERR));
	}
	return (0);
}

static int	fill_split_array(char **arr, char const *s, char c, t_parsing *par)
{
	int		start;
	int		end;
	int		i;
	char	*tmp;

	i = 0;
	end = 0;
	while (i < ft_countword(s, c))
	{
		if (get_next_word_bounds(s, c, &start, &end))
			return (0);
		tmp = ft_substr(s, start, (end - start));
		if (!tmp)
			return (parsing_error_int(par, ERR_MALLOC, EXIT_SYSTEM, ERR));
		arr[i] = extract_token_without_quotes(tmp, par);
		free(tmp);
		if (arr[i] == NULL || free_split_on_failure(par, arr, i) == ERR)
			return (ERR);
		i++;
	}
	arr[i] = NULL;
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
		parsing_error_char(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL);
		return (NULL);
	}
	if (fill_split_array(array, s, c, parsing) == ERR)
		return (NULL);
	return (array);
}
