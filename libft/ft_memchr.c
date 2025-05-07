/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:02:33 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/19 11:29:50 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memory_block, int searched_char, size_t size)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)memory_block;
	i = 0;
	while (i < size)
	{
		if (str[i] == (unsigned char)searched_char)
		{
			return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
