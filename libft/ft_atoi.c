/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:38:42 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/27 11:23:08 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	go_to_num(const char *str, int *i, int *minus)
{
	while (str[*i] == ' ' || (str[*i] > 8 && str[*i] < 14))
		*i = *i + 1;
	if (str[*i] == '+')
		*i = *i + 1;
	else if (str[*i] == '-')
	{
		*minus = -1;
		*i = *i + 1;
	}
}

/* 
** in case of int : OK
** in case of long : overflow
** in case of long long : return 0 or -1
*/
int	ft_atoi(const char *str)
{
	long	result;
	int		i;
	int		minus;

	i = 0;
	minus = 1;
	result = 0;
	go_to_num(str, &i, &minus);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > result * 10)
		{
			if (minus == 1)
				return (-1);
			else
				return (0);
		}
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return ((int)result * minus);
}
