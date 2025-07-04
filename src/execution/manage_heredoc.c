#include "minishell.h"

volatile sig_atomic_t	g_sigint = 0;

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_sigint = 1;
		rl_done = 1;
	}
}

static void	readline_heredoc(int fd, char *eof)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (g_sigint)
		{
			g_sigint = 0;
			break ;
		}
		if (!input)
		{
			msg_return(HEREDOC_EXPECT_DELIMITER, eof, 0);
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

	set_signals_on(HEREDOC_MODE);
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
