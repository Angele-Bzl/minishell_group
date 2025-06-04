# include "minishell.h"

static int		next_pipe_segment(const char *s, char c, int *start, int *end);
static int		ft_countpipe(char const *s, char c);
static int		ft_free(char **array, int i);

char	**pipe_segmentation(char const *s, char c)
{
	int		start;
	int		end;
	int		i;
	int		words;
	char	**array;

	i = 0;
	end = 0;
	words = ft_countpipe(s, c);
	if (words == -1)
		return(NULL);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	while (i < words)
	{
		if (next_pipe_segment(s, c, &start, &end) == -1)
			return (NULL);
		array[i] = ft_substr(s, start, (end - start));
		if (ft_free(array, i))
			return (NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}

static int	ft_free(char **array, int i)
{
	if (!array[i])
	{
		while (i + 1 > 0)
		{
			free(array[i]);
			i--;
		}
		free(array);
		return (1);
	}
	return (0);
}

static int	next_pipe_segment(const char *s, char c, int *start, int *end)
{
	int	pipe_count;

	pipe_count = 0;
	*start = *end;
	while (s[*start] == c || ft_isspace(s[*start]))
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
			skip_quote(s, end); // si s[i] = quote, on continue jusqu'a la prochaine
		*end = *end + 1;
	}
	return (0);
}

static int		ft_countpipe(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 1; //on commence forcement avec un node ?
	if (!s)
		return (0);
	while (ft_isspace(s[i])) // on supprime les premiers espaces //changer en isspace
		i++;
	if (s[i] == '|') // si on croise direct un pipe, syntax error
	{
		printf("syntax error\n");
		return (-1);
	}
	while (s[i])
	{
		while (ft_isspace(s[i])) //il faudra plutot mettre is space ici
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == '\"' || s[i] == '\'')
				skip_quote(s, &i); // si s[i] = quote, on continue jusqu'a la prochaine
			i++;
		}
		count++;
		if (s[i] != '\0')
			i++;
	}
	count--;
	return (count);
}
