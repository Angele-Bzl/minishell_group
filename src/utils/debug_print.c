# include "minishell.h"

void	print_prompt_tab(char **p_tab)
{
	int	i;

	i = 0;
	while (p_tab[i])
		printf("%s\n", p_tab[i++]);
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

static void	print_rafter(t_rafter *r)
{
	if (!r)
	{
		printf("NULL\n");
		return;
	}
	
	// Affichage lisible de la valeur de l'énum
	switch (*r)
	{
		case EMPTY_RAFTER:
			printf("EMPTY_RAFTER\n");
			break;
		case SIMPLE_LEFT:
			printf("SIMPLE_LEFT (<)\n");
			break;
		case DOUBLE_LEFT:
			printf("DOUBLE_LEFT (<<)\n");
			break;
		case SIMPLE_RIGHT:
			printf("SIMPLE_RIGHT (>)\n");
			break;
		case DOUBLE_RIGHT:
			printf("DOUBLE_RIGHT (>>)\n");
			break;
		case DEFAULT:
			printf("DEFAULT\n");
			break;
		default:
			printf("UNKNOWN_RAFTER\n");
	}
}

void	print_tokens(t_data *data)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	data->ls_token = data->token_head;
	while (data->ls_token)
	{
		printf("========= NODE %d =========\n\n", k);
		if (data->ls_token->cmd)
		{
			while (data->ls_token->cmd[i])
			{
				printf("Cmd %d : %s\n", i, data->ls_token->cmd[i]);
				i++;
			}
		}
		else
			printf("Cmd %d : NULL\n", i);
		printf("\n");
		printf("In_redir : ");
		print_rafter(data->ls_token->io_redir[0]);
		printf("Out_redir : ");
		print_rafter(data->ls_token->io_redir[1]);
		printf("\nIn_value : %s\n", data->ls_token->io_value[0]);
		printf("Out_value : %s\n\n", data->ls_token->io_value[1]);
		data->ls_token = data->ls_token->next;
		i = 0;
		k++;
	}
}
