# include "minishell.h"

static int	next_pipe_segment(char c, int *start, int *end, t_parsing *parsing)
{
	int	pipe_count;

	pipe_count = 0;
	*start = *end;
	while (parsing->prompt[*start] == c || ft_isspace(parsing->prompt[*start]))
	{
		if (parsing->prompt[*start] == c && ++pipe_count > 1)								// s'il y a plusieurs pipe sans rien entre les 2
		{
			ft_printf_err("syntaxe error near unexpected token '|'\n");
			parsing->errcode = ERR_PROMPT;
			return (-1);
		}
		(*start)++;
	}
	if (parsing->prompt[*start] == '\0' )
		return (0);
	*end = *start;
	while (parsing->prompt[*end] != c && parsing->prompt[*end] != '\0')
	{
		if (parsing->prompt[*end] == '\"' || parsing->prompt[*end] == '\'')
			skip_quote(parsing->prompt, end);												// si s[i] = quote, on continue jusqu'a la prochaine
		*end = *end + 1;
	}
	return (0);
}

static int	free_split_on_failure(char **array, int i, t_parsing *parsing)
{
	if (!array[i])
	{
		while (i + 1 > 0)
		{
			free(array[i]);
			i--;
		}
		free(array);
		parsing->errcode = ERR_MALLOC;
		return (-1);
	}
	return (0);
}

static int		ft_countpipe(char const *prompt, char c, t_parsing *parsing)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (prompt_begins_with_a_pipe(prompt, &i, parsing))
		return (-1);
	count = parse_pipe_segments(prompt, c, i);
	return (count);
}

static int	fill_pipe_segments(char **array, char const *prompt, char c, t_parsing *parsing)
{
	int	i = 0;
	int	start;
	int	end = 0;
	int pipe_seg;

	pipe_seg = ft_countpipe(prompt, c, parsing);
	while (i <= pipe_seg) //<= ?
	{
		if (next_pipe_segment(c, &start, &end, parsing) == -1)				// errcode a deja ete update plus haut donc on travail avec -1
			return (-1);
		array[i] = ft_substr(prompt, start, end - start);
		if (free_split_on_failure(array, i, parsing) == -1)			// errcode a deja ete update plus haut donc on travail avec -1
			return (-1);
		i++;
	}
	array[i] = NULL;
	return (0);
}

char	**pipe_segmentation(t_parsing *parsing, char c)
{
	int		pipe_seg;
	char	**array;
	char	*prompt;

	prompt = parsing->prompt;
	pipe_seg = ft_countpipe(prompt, c, parsing);
	if (pipe_seg == -1)
		return(NULL);
	array = malloc(sizeof(char *) * (pipe_seg + 2)); // + 1 ?
	if (!array)
	{
		parsing->errcode = ERR_MALLOC;
		return (NULL);
	}
	if (fill_pipe_segments(array, prompt, c, parsing) == -1)						// errcode a deja ete update plus haut donc on travail avec -1
		return (NULL);
	return (array);
}
