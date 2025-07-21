#include "minishell.h"

void	copy_till_the_end(char *new_prompt, char *old_prompt, int *i, int *j)
{
	while (old_prompt[*i])
	{
		new_prompt[*j] = old_prompt[*i];
		(*j)++;
		(*i)++;
	}
}
