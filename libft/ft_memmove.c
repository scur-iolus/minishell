/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:49:34 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/05/26 10:09:05 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst1;
	const unsigned char	*src1;

	dst1 = dst;
	src1 = src;
	i = -1;
	if (dst1 > src1)
	{
		while (++i < n)
		{
			dst1[n - i - 1] = src1[n - i - 1];
		}
	}
	else if (dst1 < src1)
	{
		while (n--)
			*dst1++ = *src1++;
	}
	return (dst);
}
