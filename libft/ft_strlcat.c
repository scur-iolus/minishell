/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:53:25 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/06/30 10:41:38 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			j;
	unsigned int	size_dst;
	unsigned int	size_src;

	j = 0;
	size_dst = ft_strlen(dst);
	size_src = ft_strlen(src);
	if (dstsize == 0)
		return (size_src);
	if (dstsize < size_dst)
		return (size_src + dstsize);
	while (src[j] && (size_dst < dstsize - 1))
	{
		dst[size_dst] = src[j];
		j++;
		size_dst++;
	}
	dst[size_dst] = '\0';
	return (ft_strlen(dst) + ft_strlen(src) - j);
}
