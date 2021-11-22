/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:05:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/22 17:33:07 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		j;

	i = -1;
	if (!s1 || !s2)
		return (0);
	while (s1[++i] && s2[i])
	{
		j = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (j != 0)
			return (j);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
