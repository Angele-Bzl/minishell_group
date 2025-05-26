# include "minishell.h"

t_token	*token_lstnew(void)
{
	t_token	*new;

	new = malloc(sizeof (t_token));
	if (!new)
		return (NULL);
	new->io_redir[0] = NULL;
	new->io_redir[1] = NULL;
	new->io_value[0] = NULL;
	new->io_value[1] = NULL;
	new->next = NULL;
	return (new);
}

static t_token	*token_lstlast(t_token *lst)
{
    t_token  *last;

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
