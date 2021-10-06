/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:19:04 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/06/29 16:14:59 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_base(int i, char *base)
{
	ft_putchar(base[i]);
}

static int	ft_error_base(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(str) < 2)
		return (0);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	i = 0;
	while (str[i])
	{
		j = 1;
		while (str[i + j])
		{
			if (str[i] == str[i + j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base_pointer(unsigned long int nbr, char *base)
{
	unsigned long int	size_base;

	size_base = ft_strlen(base);
	if (ft_error_base(base) == 1)
	{
		if (nbr >= size_base)
		{
			ft_putnbr_base_pointer(nbr / size_base, base);
			nbr %= size_base;
		}
		ft_print_base(nbr, base);
	}
}
