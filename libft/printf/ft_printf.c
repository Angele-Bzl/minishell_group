/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:53:37 by abarzila          #+#    #+#             */
/*   Updated: 2024/12/04 09:45:08 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	select_type(char const c, va_list arg, int *count)
{
	if (c == 'c')
		print_c(arg, count);
	else if (c == 's')
		print_s(arg, count);
	else if (c == 'p')
		print_p(arg, count);
	else if (c == 'd')
		print_d(arg, count);
	else if (c == 'i')
		print_d(arg, count);
	else if (c == 'u')
		print_u(arg, count);
	else if (c == 'x')
		print_small_x(arg, count);
	else if (c == 'X')
		print_big_x(arg, count);
	else if (c == '%')
		print_percent(count);
	else
	{
		ft_putchar_fd('%', 1);
		ft_putchar_fd(c, 1);
		*count += 2;
	}
	return (*count);
}

static int	is_error(const char c)
{
	char	*error;

	error = ".-+*#' 0123456789\0";
	if (ft_strchr(error, c))
	{
		return (1);
	}
	return (0);
}

static int	is_not_mplt_yet(const char c)
{
	char	*not_mplt;

	not_mplt = "aAoDnfFeEgGlCS";
	if (ft_strchr(not_mplt, c))
	{
		return (1);
	}
	return (0);
}

static int	char_is_percent(const char c, va_list arg, int *count, long *i)
{
	if (is_error(c))
	{
		va_end(arg);
		return (-1);
	}
	else if (is_not_mplt_yet(c))
	{
		write(2, "this type is not implemented in ft_printf yet.\n", 47);
		return (-1);
	}
	*count = select_type(c, arg, count);
	(*i)++;
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	arg;
	long	i;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (char_is_percent(format[i + 1], arg, &count, &i) == -1)
				return (-1);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			count++;
		}
		i++;
	}
	va_end(arg);
	return (count);
}
