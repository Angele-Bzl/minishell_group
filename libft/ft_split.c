/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:18:47 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/04 10:53:33 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

static void	free_all(char **tab, int i)
{
	i--;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static int	next_set(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (ft_strlen(s) - i);
}

static int	fill_str(char **tab, char const *s, char c, int i)
{
	int	j;
	int	counter;

	j = 0;
	counter = 0;
	while (*s != c && *s)
	{
		tab[i][j] = *s;
		j++;
		s++;
		counter++;
	}
	tab[i][j] = '\0';
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		words;
	int		i;

	words = count_words(s, c);
	tab = malloc((words + 1) * (sizeof (char *)));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		tab[i] = malloc((ft_strlen(s) - next_set(s, c) + 1) * sizeof (char));
		if (!tab[i])
		{
			free_all(tab, i);
			return (NULL);
		}
		s = s + fill_str(tab, s, c, i);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
