#include "minishell.h"

static void readline_heredoc (int fd, char *eof)
{
    char *input;

    input = NULL;
    while (1)
    {
        input = readline("> ");
        // printf("input = %s | eof = %s\n", input, eof);
        if(!ft_strncmp(input, eof, ft_strlen(eof)))
        {
            // printf("HELLO\n");
            break;
        }
        write(fd, input, ft_strlen(input));
        write(fd, "\n", 1);
        free(input);
        input = NULL;
    }
    free(input);
    input = NULL;
}

int here_doc(char *eof)
{
    int  fd;

	/*write*/
    fd = open(".infile.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        return (0);
    readline_heredoc(fd, eof);
    close (fd);

	/*read*/
    fd = open(".infile.tmp", O_RDONLY);
    if (fd == -1)
        return (0);
    unlink(".infile.tmp");
    return (fd);
}
