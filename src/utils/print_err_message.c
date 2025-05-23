#include "../../header/minishell.h"

int	err_message(t_error error)
{
	if (error == ALL_OK)
		return (0);

	if (error == ERR_CREAT)
		perror("minishell: error creating file\n");
	else if (error == ERR_ID)
		fprintf(stderr, "minishell: invalid identifier\n");
	else if (error == ERR_EXEC)
		perror("minishell: execution error\n");
	else if (error == ERR_PIPE)
		perror("minishell: pipe error\n");
	else if (error == ERR_RAFT)
		fprintf(stderr, "minishell: redirection after file truncation failed\n");
	else if (error == ERR_MALLOC)
		fprintf(stderr, "minishell: memory allocation failed\n");
	else if (error == ERR_SYNTAXE)
		fprintf(stderr, "minishell: syntax error\n");
	return (1);
}
