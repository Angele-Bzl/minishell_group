/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:33:42 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/28 17:13:17 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_s(va_list arg, int *count)
{
	char	*s;

	s = va_arg(arg, char *);
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		*count += 6;
		return ;
	}
	ft_putstr_fd(s, 1);
	*count += ft_strlen(s);
}
