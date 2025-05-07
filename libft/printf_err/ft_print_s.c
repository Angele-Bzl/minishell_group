/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:33:42 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/03 10:56:22 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_err.h"

void	print_s(va_list arg, int *count)
{
	char	*s;

	s = va_arg(arg, char *);
	if (!s)
	{
		ft_putstr_fd("(null)", 2);
		*count += 6;
		return ;
	}
	ft_putstr_fd(s, 2);
	*count += ft_strlen(s);
}
