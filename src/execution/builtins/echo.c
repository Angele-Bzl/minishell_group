/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:54:24 by abarzila          #+#    #+#             */
/*   Updated: 2025/07/22 12:54:27 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_dash(bool *new_line, bool *option, char **cmd, int i)
{
	int	j;

	j = 1;
	while (cmd[i][j] == 'n')
		j++;
	if (cmd[i][j] == '\0')
		*new_line = false;
	else
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		*option = false;
	}
}

static void	print_arg(char **cmd, int i)
{
	printf("%s", cmd[i]);
	if (cmd[i + 1])
		printf(" ");
}

void	exec_echo(char **cmd)
{
	int		i;
	bool	option;
	bool	new_line;

	new_line = true;
	option = true;
	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && option == true)
			manage_dash(&new_line, &option, cmd, i);
		else
		{
			print_arg(cmd, i);
			option = false;
		}
		i++;
	}
	if (new_line == true)
		printf("\n");
}
