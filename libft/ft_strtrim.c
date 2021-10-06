/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 22:45:23 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/05/24 09:58:26 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		else
			set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && is_charset(s1[i], set))
		i++;
	size = ft_strlen(s1);
	while (size > i && is_charset(s1[size - 1], set))
		size--;
	ptr = malloc(sizeof(char) * size - i + 1);
	if (!ptr)
		return (NULL);
	while (i < size)
		ptr[j++] = s1[i++];
	ptr[j] = 0;
	return (ptr);
}
