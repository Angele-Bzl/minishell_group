/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_big_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:32:43 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/28 16:21:28 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_big_x(int nbr, char *base_big, int *count)
{
	int	i;

	while (nbr >= 16)
	{
		putnbr_big_x(nbr / 16, base_big, count);
		nbr = nbr % 16;
	}
	i = nbr;
	write(1, &base_big[i], 1);
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
	write(1, &base_big[x], 1);
	(*count)++;
}

// void	putnbr_big_x(int nbr, char *base_big)
// {
// 	int	i;

// 	if (nbr < 0)
// 	{
// 		write(1, "-", 1);
// 		nbr *= -1;
// 	}
// 	while (nbr >= 16)
// 	{
// 		putnbr_big_x(nbr / 16, base_big);
// 		nbr = nbr % 16;
// 	}
// 	i = nbr;
// 	write(1, &base_big[i], 1);
// }

// void	print_big_x(va_list arg, int *count)
// {
// 	int		x;
// 	int		i;
// 	char	*base_big;

// 	x = va_arg(arg, int);
// 	base_big = "0123456789ABCDEF";
// 	if (x < 0)
// 	{
// 		write(1, "-", 1);
// 		x *= -1;
// 	}
// 	if (x >= 16)
// 	{
// 		putnbr_big_x(x / 16, base_big);
// 		x = x % 16;
// 		(*count)++;
// 	}
// 	i = x;
// 	write(1, &base_big[i], 1);
// 	(*count)++;
// }
