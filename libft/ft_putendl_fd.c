/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:50:21 by abarzila          #+#    #+#             */
/*   Updated: 2024/11/27 08:19:11 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
	{
		write (2, "(ft_putendl_fd) No string to write\n", 34);
		return ;
	}
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
