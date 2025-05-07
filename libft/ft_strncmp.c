/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:58:49 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/21 16:11:01 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	while (c1[i] && c2[i] && i < n)
	{
		if (c1[i] > c2[i])
			return (1);
		if (c1[i] < c2[i])
			return (-1);
		i++;
	}
	if (i < n)
	{
		if (c1[i] > c2[i])
			return (1);
		if (c1[i] < c2[i])
			return (-1);
	}
	return (0);
}
