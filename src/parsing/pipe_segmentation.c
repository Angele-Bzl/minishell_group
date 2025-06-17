# include "minishell.h"

static int	next_pipe_segment(const char *s, char c, int *start, int *end, int *errcode)
{
	int	pipe_count;

	pipe_count = 0;
	*start = *end;
	while (s[*start] == c || ft_isspace(s[*start]))
	{
		if (s[*start] == c && ++pipe_count > 1)								// s'il y a plusieurs pipe sans rien entre les 2
		{
			ft_printf_err("syntaxe error near unexpected token '|'\n");
			*errcode = ERR_PROMPT;
			return (ERR_PROMPT);
		}
		(*start)++;
	}
	if (s[*start] == '\0' )
		return (OK);
	*end = *start;
	while (s[*end] != c && s[*end] != '\0')
	{
		if (s[*end] == '\"' || s[*end] == '\'')
			skip_quote(s, end);												// si s[i] = quote, on continue jusqu'a la prochaine
		*end = *end + 1;
	}
	return (OK);
}

static int	free_split_on_failure(char **array, int i, int *errcode)
{
	if (!array[i])
	{
		while (i + 1 > 0)
		{
			free(array[i]);
			i--;
		}
		free(array);
		*errcode = ERR_MALLOC;
		return (ERR_MALLOC);
	}
	return (OK);
}

static int		ft_countpipe(char const *s, char c, int *errcode)
{
	int		i;
	int		count;
	int		check;

	i = 0;
	count = 0;
	if (!s)
		return (-1);
	check = prompt_begins_with_a_pipe(s, &i, errcode);
	if (check != OK)
		return (check);
	count = parse_pipe_segments(s, c, i);
	return (count);
}

static int	fill_pipe_segments(char **array, char const *s, char c, int *errcode)
{
	int	i = 0;
	int	start;
	int	end = 0;
	int pipe_seg;

	pipe_seg = ft_countpipe(s, c, errcode);
	while (i <= pipe_seg)
	{
		if (next_pipe_segment(s, c, &start, &end, errcode) == ERR_PROMPT)	// errcode a deja ete update plus haut donc on travail avec -1
			return (-1);
		array[i] = ft_substr(s, start, end - start);
		if (free_split_on_failure(array, i, errcode) == ERR_MALLOC)			// errcode a deja ete update plus haut donc on travail avec -1
			return (-1);
		i++;
	}
	array[i] = NULL;
	return (0);
}

char	**pipe_segmentation(char const *s, char c, int *errcode)
{
	int		pipe_seg;
	char	**array;

	pipe_seg = ft_countpipe(s, c, errcode);
	if (pipe_seg == ERR_PROMPT)
		return(NULL);
	array = malloc(sizeof(char *) * (pipe_seg + 1));
	if (!array)
	{
		*errcode = ERR_MALLOC;
		return (NULL);
	}
	if (fill_pipe_segments(array, s, c, errcode) == -1)						// errcode a deja ete update plus haut donc on travail avec -1
		return (NULL);
	return (array);
}
