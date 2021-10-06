/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:52:34 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/06/29 16:08:57 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int	num;

	num = n;
	if (num < 0)
	{
		write(1, "-", 1);
		num *= -1;
	}
	if (num > 9)
	{
		ft_putnbr(num / 10);
		num = num % 10;
	}
	ft_putchar(num + '0');
}
