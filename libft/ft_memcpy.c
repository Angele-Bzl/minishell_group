/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:35:55 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/19 11:27:24 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*f_dest;
	const unsigned char	*f_src;

	if (dest == 0 && src == 0)
	{
		return (NULL);
	}
	f_dest = dest;
	f_src = src;
	i = 0;
	while (i < n)
	{
		f_dest[i] = f_src[i];
		i++;
	}
	return (dest);
}
