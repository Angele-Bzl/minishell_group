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
			parsing->errcode = ERR_PROMPT;
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
		parsing->errcode = ERR_MALLOC;
		return (-1);
	}
	return (0);
}

static int	ft_countpipe(char const *prompt, t_parsing *parsing)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (prompt_begins_with_a_pipe(prompt, &i, parsing))
		return (-1);
	count = parse_pipe_segments(prompt, i);
	return (count);
}

static int	fill_pipe_segments(char **array, char const *prompt, t_parsing *par)
{
	int	i;
	int	start;
	int	end;
	int	pipe_seg;

	pipe_seg = ft_countpipe(prompt, par);
	i = 0;
	end = 0;
	while (i <= pipe_seg)
	{
		if (next_pipe_segment(&start, &end, par) == -1)
			return (-1);
		array[i] = ft_substr(prompt, start, end - start);
		if (free_split_on_failure(array, i, par) == -1)
			return (-1);
		i++;
	}
	array[i] = NULL;
	return (0);
}

char	**pipe_segmentation(t_parsing *parsing)
{
	int		pipe_seg;
	char	**array;

	pipe_seg = ft_countpipe(parsing->prompt, parsing);
	if (pipe_seg == -1)
		return (NULL);
	array = malloc(sizeof(char *) * (pipe_seg + 2));
	if (!array)
	{
		parsing->errcode = ERR_MALLOC;
		return (NULL);
	}
	if (fill_pipe_segments(array, parsing->prompt, parsing) == -1)
		return (NULL);
	return (array);
}
