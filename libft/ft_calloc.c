/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:02:50 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/27 08:10:23 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void		*result;

	if (count == 0 || size == 0)
	{
		result = malloc(0);
		if (!result)
			return (NULL);
		return (result);
	}
	if (count > SIZE_MAX / size)
		return (NULL);
	result = malloc(count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}
