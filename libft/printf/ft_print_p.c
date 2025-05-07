/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:33:06 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/29 09:50:25 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_p(va_list arg, int *count)
{
	void				*p;
	char				*base_small;
	unsigned long		ul_p;

	p = va_arg(arg, void *);
	if (!p)
	{
		write(1, "(nil)", 5);
		*count += 5;
		return ;
	}
	ul_p = (unsigned long)p;
	base_small = "0123456789abcdef";
	write(1, "0x", 2);
	*count += 2;
	if (ul_p >= 16)
	{
		putnbr_small_x(ul_p / 16, base_small, count);
	}
	ul_p = ul_p % 16;
	write(1, &base_small[ul_p], 1);
	(*count)++;
}
