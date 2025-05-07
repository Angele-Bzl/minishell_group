/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:30:16 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/28 10:51:54 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(va_list arg, int *count)
{
	char	ch;

	ch = va_arg(arg, int);
	ft_putchar_fd(ch, 1);
	(*count)++;
}
