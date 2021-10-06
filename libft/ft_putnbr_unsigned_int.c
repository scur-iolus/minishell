/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:30:54 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/06/29 16:14:19 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_unsigned_int(unsigned int n)
{
	unsigned long int	num;

	num = n;
	if (num > 9)
	{
		ft_putnbr(num / 10);
		num = num % 10;
	}
	ft_putchar(num + '0');
}
