#include "minishell.h"

static int	is_expandable(char current_i, char next_i, t_parsing *parsing)
{
	if (current_i != '$')
		return (0);
	if (parsing->simple_quote == true)
		return (0);
	if (ft_isspace(next_i))
		return (0);
	if (next_i == '\0')
		return (0);
	if (next_i == '\"' && parsing->double_quote == true)
		return (0);
	if (next_i == '=')
		return (0);
	return (1);
}

void	quote_check(char c, t_parsing *parsing)
{
	if (c == '\"'
		&& parsing->double_quote == false
		&& parsing->simple_quote == false)
		parsing->double_quote = true;
	else if (c == '\"'
		&& parsing->double_quote == true
		&& parsing->simple_quote == false)
		parsing->double_quote = false;
	else if (c == '\''
		&& parsing->simple_quote == false
		&& parsing->double_quote == false)
		parsing->simple_quote = true;
	else if (c == '\''
		&& parsing->simple_quote == true
		&& parsing->double_quote == false)
		parsing->simple_quote = false;
}

static int	dollar_remaining(char *str, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (str[i])
	{
		quote_check(str[i], parsing);
		if (str[i] == '$'
			&& parsing->simple_quote == false
			&& !ft_isspace(str[i + 1])
			&& str[i + 1] != '\0'
			&& str[i + 1] != '\"'
			&& str[i + 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

void	expand_var(t_parsing *par)
{
	par->pipe_seg = 0;
	par->p_index = 0;
	while (par->prompt_tab[par->pipe_seg])
	{
		while (par->prompt_tab[par->pipe_seg][par->p_index])
		{
			quote_check(par->prompt_tab[par->pipe_seg][par->p_index], par);
			if (is_expandable(par->prompt_tab[par->pipe_seg][par->p_index],
				par->prompt_tab[par->pipe_seg][par->p_index + 1], par))
			{
				manage_dollar_sign(par);
				if (par->errcode != ALL_OK
					|| !par->prompt_tab[par->pipe_seg][par->p_index])
					return ;
			}
			par->p_index++;
		}
		if (!dollar_remaining(par->prompt_tab[par->pipe_seg], par))
			par->pipe_seg++;
		par->p_index = 0;
	}
	par->double_quote = false;
	par->simple_quote = false;
}
