/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:53:26 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/05/24 13:24:41 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	l_src;
	size_t	x;

	if (!dst && !src)
		return (0);
	l_src = ft_strlen(src);
	i = 0;
	x = 0;
	if (dstsize)
	{
		if (l_src >= dstsize)
			x++;
		while (i < dstsize - x && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
