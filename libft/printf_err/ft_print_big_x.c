/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_big_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:32:43 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/03 10:56:39 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_err.h"

void	putnbr_big_x(int nbr, char *base_big, int *count)
{
	int	i;

	while (nbr >= 16)
	{
		putnbr_big_x(nbr / 16, base_big, count);
		nbr = nbr % 16;
	}
	i = nbr;
	write(2, &base_big[i], 1);
	(*count)++;
}

void	print_big_x(va_list arg, int *count)
{
	unsigned int		x;
	char				*base_big;

	x = va_arg(arg, unsigned int);
	base_big = "0123456789ABCDEF";
	if (x >= 16)
	{
		putnbr_big_x(x / 16, base_big, count);
	}
	x = x % 16;
	write(2, &base_big[x], 1);
	(*count)++;
}
