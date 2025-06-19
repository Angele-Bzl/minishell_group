# include "minishell.h"

t_outfile	*outfile_lstnew(void)
{
	t_outfile	*new;

	new = malloc(sizeof (t_outfile));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static t_outfile	*outfile_lstlast(t_outfile *lst)
{
    t_outfile  *last;

	if (!lst)
		return (NULL);
    last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	outfile_lstadd_back(t_outfile **lst, t_outfile *new)
{
	t_outfile	*current;

	if (!lst)
		return ;
	current = outfile_lstlast(*lst);
	if (current)
        current->next = new;
	else
        *lst = new;
}
