/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:30:17 by maballet          #+#    #+#             */
/*   Updated: 2025/07/22 15:30:18 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	file_init(t_file *file)
{
	file->next = NULL;
	file->redirection = DEFAULT;
	file->value = NULL;
}

t_token	*token_lstnew(void)
{
	t_token	*new;

	new = malloc(sizeof (t_token));
	if (!new)
		return (NULL);
	new->ls_infile = malloc(sizeof(t_file));
	if (!new->ls_infile)
	{
		ft_putstr_fd(MALLOC, STDERR_FILENO);
		free(new);
		return (NULL);
	}
	file_init(new->ls_infile);
	new->ls_outfile = malloc(sizeof(t_file));
	if (!new->ls_outfile)
	{
		ft_putstr_fd(MALLOC, STDERR_FILENO);
		free(new->ls_infile);
		free(new);
		return (NULL);
	}
	file_init(new->ls_outfile);
	new->next = NULL;
	new->cmd = NULL;
	return (new);
}

t_token	*token_lstlast(t_token *lst)
{
	t_token	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!lst)
		return ;
	current = token_lstlast(*lst);
	if (current)
		current->next = new;
	else
		*lst = new;
}
