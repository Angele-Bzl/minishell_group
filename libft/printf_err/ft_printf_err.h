/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:54:15 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/03 10:55:12 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_ERR_H

# define FT_PRINTF_ERR_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

int		ft_printf_err(const char *format, ...);
void	print_c(va_list arg, int *count);
void	print_s(va_list arg, int *count);
void	print_p(va_list arg, int *count);
void	print_d(va_list arg, int *count);
void	print_percent(int *count);
void	print_big_x(va_list arg, int *count);
void	putnbr_big_x(int nbr, char *base_big, int *count);
void	print_small_x(va_list arg, int *count);
void	putnbr_small_x(unsigned long nbr, char *base_small, int *count);
void	print_u(va_list arg, int *count);

#endif
