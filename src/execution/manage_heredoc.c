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

static int	readline_heredoc(int fd, char *eof)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (g_sigint)
		{
			g_sigint = 0;
			free(input);
			return(HEREDOC_INTERRUPTED);
		}
		if (!input)
		{
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
	return (0);
}

int	here_doc(char *eof)
{
	int	fd;
	int	ret;

	set_signals_on(HEREDOC_MODE);
	fd = open(TMP, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	ret = readline_heredoc(fd, eof);
	close (fd);
		if (ret == HEREDOC_INTERRUPTED)
	{
		unlink(TMP);
		return (HEREDOC_INTERRUPTED);
	}
	fd = open(TMP, O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(TMP);
	return (fd);
}
