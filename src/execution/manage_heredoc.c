#include "minishell.h"

static void	readline_heredoc(int fd, char *eof)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			// Ctrl+D : EOF
			ft_printf_err("bash: warning: heredoc delimited by end_of_file (wanted `%s')\n", eof);
			break ;
		}
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

	set_heredoc_signals();
	fd = open(TMP, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	readline_heredoc(fd, eof);
	close (fd);
	fd = open(TMP, O_RDONLY);
	if (fd == -1)
		return (0);
	unlink(TMP);
	return (fd);
}
