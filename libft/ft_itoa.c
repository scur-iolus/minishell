/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:08:06 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/05/21 11:08:23 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_int(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	num;
	char	*ptr;
	int		size;

	num = n;
	size = size_int(n);
	ptr = malloc(sizeof(char) * size + 1);
	if (!ptr)
		return (NULL);
	ptr[size--] = 0;
	if (num < 0)
	{
		ptr[0] = '-';
		num *= -1;
	}
	if (num == 0)
		ptr[0] = '0';
	while (num)
	{
		ptr[size--] = (num % 10) + '0';
		num /= 10;
	}
	return (ptr);
}
