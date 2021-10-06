/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:12:24 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/06/29 16:11:16 by fmonbeig         ###   ########.fr       */
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

void	ft_putnbr_base(unsigned int nbr, char *base)
{
	unsigned int	i;
	unsigned int	size_base;

	size_base = ft_strlen(base);
	i = nbr;
	if (ft_error_base(base) == 1)
	{
		while (i >= size_base)
		{
			ft_putnbr_base(i / size_base, base);
			i %= size_base;
		}
		ft_print_base(i, base);
	}
}
