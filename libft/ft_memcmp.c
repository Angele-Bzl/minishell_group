/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:29:15 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/22 18:03:49 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		delta;

	i = 0;
	while (i < n)
	{
		delta = *(unsigned char *)s1 - *(unsigned char *)s2;
		if (delta > 0)
		{
			return (1);
		}
		else if (delta < 0)
		{
			return (-1);
		}
		s1++;
		s2++;
		i++;
	}
	return (0);
}
