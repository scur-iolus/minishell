/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:07:53 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/07 14:32:36 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(const char *str, char c)
{
	int	i;
	int	count;
	int	state;

	state = 1;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			state = 1;
		}
		else if (str[i] != c && state == 1)
		{
			state = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static int	size_word(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	**malloc_word(int words, char **ptr, char const *s, char c)
{
	int	i;
	int	index;

	index = -1;
	while (++index < words)
	{
		while (*s == c)
			s++;
		ptr[index] = malloc(sizeof(char) * (size_word(s, c) + 1));
		if (!ptr[index])
		{
			while (--index >= 0)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}
		i = 0;
		while (*s != c && *s)
			ptr[index][i++] = *s++;
		ptr[index][i] = 0;
	}
	ptr[index] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		words;

	if (!s || !(*str))
		return (NULL);
	words = wordcount(s, c);
	ptr = malloc(sizeof(char *) * (words + 1));
	if (!ptr)
		return (NULL);
	return (malloc_word(words, ptr, s, c));
}
