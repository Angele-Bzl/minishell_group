#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>
#include <signal.h>

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
		rl_event_hook = takes_a_value;
		input = readline("> ");
		if (g_sigint)
		{
			g_sigint = 0;
			free(input);
			return (HEREDOC_INTERRUPTED);
		}
		if (!input)
			return (msg_return(HDOC_EXPECT_EOF, eof, 0));
		if (!ft_strncmp(input, eof, ft_strlen(eof)))
			break ;
		ft_putendl_fd(input, fd);
		free(input);
		input = NULL;
	}
	free(input);
	input = NULL;
	return (0);
}

static int	change_tmp_name(char *tmp, int i)
{
	if (tmp[i] < 90)
		tmp[i] = tmp[i] + 1;
	else if (i > 0)
	{
		if (change_tmp_name(tmp, i - 1) == ERR)
			return (ERR);
	}
	else
		return (ERR);
	return (OK);
}

static char	*generate_name_tmp()
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(".AAAAAAAAAA.tmp");
	if (!tmp)
		return (msg_return_str(MALLOC, NULL, NULL));
	while (1)
	{
		if (!access(tmp, F_OK))
		{
			i = 10;
			if (change_tmp_name(tmp, i) == ERR)
				return (msg_return_str(HEREDOC_NAME, NULL, NULL));
		}
		else
			return (tmp);
	}
}

int	here_doc(char *eof)
{
	int	fd;
	int	ret;
	char	*tmp;

	tmp = generate_name_tmp();
	if (!tmp)
		return (ERR);
	set_signals_on(HEREDOC_MODE);
	fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (ERR);
	ret = readline_heredoc(fd, eof);
	close (fd);
	if (ret == HEREDOC_INTERRUPTED)
	{
		unlink(tmp);
		return (HEREDOC_INTERRUPTED);
	}
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
		return (ERR);
	unlink(tmp);
	return (fd);
}
