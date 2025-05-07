/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:04:04 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/25 14:33:12 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_negative(int *n, int *nb_of_char)
{
	int	is_neg;

	is_neg = 0;
	if (*n < 0)
	{
		*n = *n * -1;
		*nb_of_char = *nb_of_char + 1;
		is_neg = 1;
	}
	return (is_neg);
}

static void	count_char(int n, int *index, int *nb_of_char)
{
	if (n == 0)
	{
		*nb_of_char = *nb_of_char + 1;
	}
	*index = n;
	while (*index > 0)
	{
		*index /= 10;
		*nb_of_char = *nb_of_char + 1;
	}
}

char	*ft_itoa(int n)
{
	int		nb_of_char;
	int		index;
	char	*result;
	int		is_neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nb_of_char = 0;
	is_neg = is_negative(&n, &nb_of_char);
	count_char(n, &index, &nb_of_char);
	result = malloc(nb_of_char + 1);
	if (!result)
		return (NULL);
	result[nb_of_char] = '\0';
	nb_of_char--;
	while (nb_of_char >= index)
	{
		if (nb_of_char == 0 && is_neg)
			result[nb_of_char] = '-';
		else
			result[nb_of_char] = (n % 10) + 48;
		nb_of_char--;
		n /= 10;
	}
	return (result);
}
