/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:53:57 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/19 11:29:43 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*f_dest;
	const unsigned char	*f_src;

	f_dest = dest;
	f_src = src;
	i = 0;
	if (dest == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		if (dest > src)
			f_dest[n - (i + 1)] = f_src[n - (i + 1)];
		else
			f_dest[i] = f_src[i];
		i++;
	}
	return (dest);
}
