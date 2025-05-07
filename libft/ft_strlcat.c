/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:21:42 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/19 11:29:05 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen_b;

	destlen_b = ft_strlen(dest);
	i = 0;
	if (size <= destlen_b)
		return (ft_strlen(src) + size);
	while (i < size && src[i] && size > destlen_b + 1)
	{
		dest[destlen_b + i] = src[i];
		if (destlen_b + (i + 2) == size)
		{
			dest[destlen_b + i + 1] = '\0';
			return (destlen_b + ft_strlen(src));
		}
		i++;
	}
	dest[destlen_b + i] = '\0';
	return (destlen_b + ft_strlen(src));
}
