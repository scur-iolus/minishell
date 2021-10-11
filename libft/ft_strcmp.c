/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:05:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/11 17:08:47 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		j;

	i = -1;
	if (!s1 && !s2)
		return (0);
	while (s1[++i] || s2[i])
	{
		j = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (j == 0)
			continue ;
		else
		return (j);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
