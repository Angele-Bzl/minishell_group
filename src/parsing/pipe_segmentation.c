#include "minishell.h"

static int	next_pipe_segment(int *start, int *end, t_parsing *parsing)
{
	int	pipe_count;

	pipe_count = 0;
	*start = *end;
	while (parsing->prompt[*start] == '|'
		|| ft_isspace(parsing->prompt[*start]))
	{
		if (parsing->prompt[*start] == '|' && ++pipe_count > 1)
		{
			parsing_error_int(parsing, ERR_PROMPT, EXIT_SYSTEM, 0);
			return (msg_return(ERR_SYNTAX_NEAR, "|", ERR));
		}
		(*start)++;
	}
	if (parsing->prompt[*start] == '\0' )
		return (0);
	*end = *start;
	while (parsing->prompt[*end] != '|' && parsing->prompt[*end] != '\0')
	{
		if (parsing->prompt[*end] == '\"' || parsing->prompt[*end] == '\'')
			skip_quote(parsing->prompt, end);
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
		return (parsing_error_int(parsing, ERR_MALLOC, EXIT_SYSTEM, ERR));
	}
	return (0);
}

static int	ft_countpipe(char const *prompt, t_parsing *parsing)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (prompt_begins_with_a_pipe(prompt, &i))
		return (parsing_error_int(parsing, ERR_PROMPT, EXIT_SYSTEM, ERR));
	count = parse_pipe_segments(prompt, i);
	return (count);
}

static int	fill_pipe_segments(char **array, char const *prompt, t_parsing *par)
{
	int	i;
	int	start;
	int	end;
	int	pipe_count;

	pipe_count = ft_countpipe(prompt, par);
	if (pipe_count == ERR)
		return (ERR);
	i = 0;
	end = 0;
	while (i <= pipe_count)
	{
		if (next_pipe_segment(&start, &end, par) == ERR)
			return (ERR);
		array[i] = ft_substr(prompt, start, end - start);
		if (!array[i])
			return (parsing_error_int(par, ERR_MALLOC, EXIT_SYSTEM, ERR));
		if (free_split_on_failure(array, i, par) == ERR)
			return (ERR);
		i++;
	}
	array[i] = NULL;
	return (0);
}

char	**pipe_segmentation(t_parsing *parsing)
{
	int		pipe_count;
	char	**array;

	pipe_count = ft_countpipe(parsing->prompt, parsing);
	if (pipe_count == ERR)
		return (NULL);
	array = malloc(sizeof(char *) * (pipe_count + 2));
	if (!array)
	{
		parsing_error_char(parsing, ERR_MALLOC, EXIT_SYSTEM, NULL);
		return (NULL);
	}
	if (fill_pipe_segments(array, parsing->prompt, parsing) == ERR)
		return (NULL);
	return (array);
}
