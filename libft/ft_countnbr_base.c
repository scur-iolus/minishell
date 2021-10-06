/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countnbr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 12:19:20 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/06/29 16:05:35 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	ft_countnbr_base(unsigned int nbr, char *base)
{
	unsigned int		i;
	unsigned int		size_base;
	int					count;

	count = 0;
	size_base = ft_strlen(base);
	i = nbr;
	if (i == 0)
		return (1);
	if (ft_error_base(base) == 1)
	{
		while (i > 0)
		{
			i /= size_base;
			count++;
		}
	}
	return (count);
}
