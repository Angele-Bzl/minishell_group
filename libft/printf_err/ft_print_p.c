/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:33:06 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/03 10:56:28 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_err.h"

void	print_p(va_list arg, int *count)
{
	void				*p;
	char				*base_small;
	unsigned long		ul_p;

	p = va_arg(arg, void *);
	if (!p)
	{
		write(2, "(nil)", 5);
		*count += 5;
		return ;
	}
	ul_p = (unsigned long)p;
	base_small = "0123456789abcdef";
	write(2, "0x", 2);
	*count += 2;
	if (ul_p >= 16)
	{
		putnbr_small_x(ul_p / 16, base_small, count);
	}
	ul_p = ul_p % 16;
	write(2, &base_small[ul_p], 1);
	(*count)++;
}
