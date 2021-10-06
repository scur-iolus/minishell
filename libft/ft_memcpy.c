/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:54:06 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/05/26 10:07:35 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst1;
	const unsigned char	*src1;

	if (!dst && !src)
		return (NULL);
	dst1 = dst;
	src1 = src;
	while (n)
	{
		*dst1 = *src1;
		dst1++;
		src1++;
		n--;
	}
	return (dst);
}
