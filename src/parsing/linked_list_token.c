# include "minishell.h"

t_token	*token_lstnew(void)
{
	t_token	*new;

	new = malloc(sizeof (t_token));
	if (!new)
		return (NULL);
	new->ls_infile = malloc(sizeof(t_infile));
	if (!new->ls_infile)
	{
		free(new);
		return (NULL);
	}
	new->ls_infile->next = NULL;
	new->ls_infile->redirection = DEFAULT;
	new->ls_infile->value = NULL;
	new->ls_outfile = malloc(sizeof(t_outfile));
	if (!new->ls_outfile)
	{
		free(new->ls_infile);
		free(new);
		return (NULL);
	}
	new->ls_outfile->next = NULL;
	new->ls_outfile->redirection = DEFAULT;
	new->ls_outfile->value = NULL;
	new->next = NULL;
	return (new);
}

t_token	*token_lstlast(t_token *lst)
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
