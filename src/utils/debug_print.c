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
	int i;

	i = 1;
	printf("env tab :\n\n");
	while (env)
	{
		printf("%d) %s\n", i, env->line);
		env = env->next;
		i++;
	}
}

// static void	print_rafter(t_rafter *r)
// {
// 	if (!r)
// 	{
// 		printf("NULL\n");
// 		return;
// 	}

// 	// Affichage lisible de la valeur de l'énum
// 	switch (*r)
// 	{
// 		case EMPTY_RAFTER:
// 			printf("EMPTY_RAFTER\n");
// 			break;
// 		case SIMPLE_LEFT:
// 			printf("SIMPLE_LEFT (<)\n");
// 			break;
// 		case DOUBLE_LEFT:
// 			printf("DOUBLE_LEFT (<<)\n");
// 			break;
// 		case SIMPLE_RIGHT:
// 			printf("SIMPLE_RIGHT (>)\n");
// 			break;
// 		case DOUBLE_RIGHT:
// 			printf("DOUBLE_RIGHT (>>)\n");
// 			break;
// 		case DEFAULT:
// 			printf("DEFAULT\n");
// 			break;
// 		default:
// 			printf("UNKNOWN_RAFTER\n");
// 	}
// }

void	print_tokens(t_data *data)
{
	int			i;
	int 		k;
	int			j;
	t_token		*current;
	t_infile	*cur_in;
	t_outfile	*cur_out;

	i = 0;
	k = 0;
	j = 0;
	current = data->ls_token;
	cur_in = data->ls_token->ls_infile;
	cur_out = data->ls_token->ls_outfile;
	while (current)
	{
		printf("========= NODE (%d) =========\n\n", k);
		if (current->cmd)
		{
			while (current->cmd[i])
			{
				printf("Cmd %d : %s\n", i, current->cmd[i]);
				i++;
			}
		}
		else
			printf("Cmd %d : NULL\n", i);
		printf("\n");
		printf("INFILES :\n");
		while(cur_in)
		{
			printf("in_node(%d)\n", j);
			printf("redir: %d\n", cur_in->redirection);
			printf("value: %s\n\n", cur_in->value);
			cur_in = cur_in->next;
			j++;
		}
		j = 0;
		printf("OUTFILES :\n");
		while(cur_out)
		{
			printf("in_node(%d)\n", j);
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
