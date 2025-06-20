# include "minishell.h"

t_infile	*infile_lstnew(void)
{
	t_infile	*new;

	new = malloc(sizeof (t_infile));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static t_infile	*infile_lstlast(t_infile *lst)
{
    t_infile  *last;

	if (!lst)
		return (NULL);
    last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	infile_lstadd_back(t_infile **lst, t_infile *new)
{
	t_infile	*current;

	if (!lst)
		return ;
	current = infile_lstlast(*lst);
	if (current)
        current->next = new;
	else
        *lst = new;
}
