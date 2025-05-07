/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_small_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:32:15 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/29 09:48:50 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_small_x(unsigned long nbr, char *base_small, int *count)
{
	if (nbr >= 16)
	{
		putnbr_small_x(nbr / 16, base_small, count);
		nbr = nbr % 16;
	}
	write(1, &base_small[nbr], 1);
	(*count)++;
}

void	print_small_x(va_list arg, int *count)
{
	unsigned int		x;
	char				*base_small;

	x = va_arg(arg, unsigned int);
	base_small = "0123456789abcdef";
	if (x >= 16)
	{
		putnbr_small_x(x / 16, base_small, count);
	}
	x = x % 16;
	write(1, &base_small[x], 1);
	(*count)++;
}
