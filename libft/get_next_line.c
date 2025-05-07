/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:02:48 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/05 08:38:50 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*mmv(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*f_dest;
	const unsigned char	*f_src;

	f_dest = dest;
	f_src = src;
	if (dest == 0 && src == 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		f_dest[i] = f_src[i];
		i++;
	}
	return (dest);
}

static char	*ft_strnjoin(char *old_line, char const *buf, int size)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof (char) * (slen(old_line) + size + 1));
	if (!str || !buf)
	{
		free(old_line);
		return (NULL);
	}
	i = 0;
	while (old_line && old_line[i])
	{
		str[i] = old_line[i];
		i++;
	}
	j = 0;
	while (buf[j] && j < size)
	{
		str[i + j] = buf[j];
		j++;
	}
	str[i + j] = '\0';
	clear_line(old_line);
	return (str);
}

static char	*create_line(char *buf, char *line, int fd)
{
	ssize_t	count_bytes;
	int		i;

	count_bytes = BUFFER_SIZE;
	while (1)
	{
		if (!buf[0])
		{
			count_bytes = read(fd, buf, BUFFER_SIZE);
			if (count_bytes == 0)
				return (line);
			if (count_bytes == -1)
				return (clear_line(line));
		}
		i = 0;
		while (buf[i] && buf[i] != '\n')
			i++;
		line = ft_strnjoin(line, buf, (i + (buf[i] == '\n')));
		if (!line)
			return (NULL);
		buf = mmv(buf, buf + (i + (buf[i] == '\n')), slen(buf));
		if (line[slen(line) - 1] == '\n')
			return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	line = create_line(buf, line, fd);
	return (line);
}
