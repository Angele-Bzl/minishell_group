#include "minishell.h"

void	print_prompt_tab(char **p_tab)
{
	int	i;

	i = 0;
	while (p_tab[i])
	{
		printf("prompt_tab[%d] : %s\n", i, p_tab[i]);
		i++;
	}
	printf("prompt_tab[%d] : %s\n", i, p_tab[i]);
}

void	print_env(t_env *env)
{
	int	i;

	i = 1;
	printf("env tab :\n\n");
	while (env)
	{
		printf("%d) %s\n", i, env->line);
		env = env->next;
		i++;
	}
}

void	print_tokens(t_data *data)
{
	int			i;
	int			j;
	int			k;
	t_token		*current;
	t_file		*cur_in;
	t_file		*cur_out;

	k = 0;
	current = data->ls_token;
	while (current)
	{
		cur_in = current->ls_infile;
		cur_out = current->ls_outfile;
		printf("========= NODE (%d) =========\n\n", k);
		if (current->cmd)
		{
			i = 0;
			while (current->cmd[i])
			{
				printf("Cmd %d : %s\n", i, current->cmd[i]);
				i++;
			}
		}
		printf("\n");
		printf("INFILES :\n");
		j = 0;
		while (cur_in)
		{
			printf("in_node(%d)\n", j);
			printf("redir: %d\n", cur_in->redirection);
			printf("value: %s\n\n", cur_in->value);
			cur_in = cur_in->next;
			j++;
		}
		j = 0;
		printf("OUTFILES :\n");
		while (cur_out)
		{
			printf("out_node(%d)\n", j);
			printf("redir: %d\n", cur_out->redirection);
			printf("value: %s\n\n", cur_out->value);
			cur_out = cur_out->next;
			j++;
		}
		j = 0;
		printf("========= END OF NODE %d =\n\n", k);
		current = current->next;
		i = 0;
		k++;
	}
}
