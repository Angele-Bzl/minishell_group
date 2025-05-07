/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:32:14 by abarzila          #+#    #+#             */
/*   Updated: 2025/05/06 17:55:58 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
    t_list  *last;

	if (!lst)
		return (NULL);
    last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}
