/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:30:50 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/03 10:56:32 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_err.h"

static void	ft_putnbr_fd_printf(int n, int fd, int *count)
{
	char	mod;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd_printf(n / 10, fd, count);
	}
	mod = (n % 10) + 48;
	write(fd, &mod, 1);
	(*count)++;
}

void	print_d(va_list arg, int *count)
{
	int		d;
	char	mod;

	d = va_arg(arg, int);
	if (d == -2147483648)
	{
		write(2, "-2147483648", 11);
		*count += 11;
		return ;
	}
	if (d < 0)
	{
		write(2, "-", 1);
		(*count)++;
		d *= -1;
	}
	if (d >= 10)
	{
		ft_putnbr_fd_printf(d / 10, 2, count);
	}
	mod = (d % 10) + 48;
	write(2, &mod, 1);
	(*count)++;
}
