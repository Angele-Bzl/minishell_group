#include "minishell.h"

void	find_all_cmds(char *clean_cmd, char *prompt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prompt[i])
	{
		while (ft_isspace(prompt[i]))
			i++;
		if (prompt[i] == '<' || prompt[i] == '>')
			i = skip_io(prompt, i);
		extract_current_cmd(prompt, &i, &j, clean_cmd);
		if (prompt[i] && prompt[i] != '<' && prompt[i] != '>')
			clean_cmd[j++] = ' ';
	}
	if (j > 0 && clean_cmd[j - 1] == ' ')
		j--;
	clean_cmd[j] = '\0';
}
