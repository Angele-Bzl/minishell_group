/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:22:52 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/19 11:29:02 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size <= 0)
	{
		return (ft_strlen(src));
	}
	while (i <= size && i <= ft_strlen(src))
	{
		dest[i] = src[i];
		if (i == size - 1)
		{
			dest[i] = '\0';
			return (ft_strlen(src));
		}
		i++;
	}
	return (ft_strlen(src));
}
