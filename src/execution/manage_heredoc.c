#include "minishell.h"

static void	readline_heredoc(int fd, char *eof)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (!ft_strncmp(input, eof, ft_strlen(eof)))
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = NULL;
	}
	free(input);
	input = NULL;
}

int	here_doc(char *eof)
{
	int	fd;

	fd = open(TMP, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	readline_heredoc(fd, eof);
	close (fd);
	fd = open(TMP, O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(TMP);
	return (fd);
}
