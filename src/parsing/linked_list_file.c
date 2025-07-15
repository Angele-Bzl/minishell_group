#include "minishell.h"

t_file	*file_lstnew(void)
{
	t_file	*new;

	new = malloc(sizeof (t_file));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static t_file	*file_lstlast(t_file *lst)
{
	t_file	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	file_lstadd_back(t_file **lst, t_file *new)
{
	t_file	*current;

	if (!lst)
		return ;
	current = file_lstlast(*lst);
	if (current)
		current->next = new;
	else
		*lst = new;
}
