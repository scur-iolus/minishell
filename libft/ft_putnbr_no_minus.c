/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_no_minus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 09:49:33 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/06/29 16:08:17 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_no_minus(int n)
{
	long int	num;

	num = n;
	if (num < 0)
		num *= -1;
	if (num > 9)
	{
		ft_putnbr(num / 10);
		num = num % 10;
	}
	ft_putchar(num + '0');
}
