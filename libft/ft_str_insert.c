/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:40:26 by llalba            #+#    #+#             */
/*   Updated: 2021/11/09 16:39:19 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_insert_o_copy(char *old, char *new, char c, size_t position)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (!(new[position]) && i == position)
			new[j] = c;
		else
		{
			new[j] = old[i];
			i++;
		}
		j++;
	}
	return (new);
}

void	ft_str_insert(char **str, char c, size_t position)
{
	size_t	new_len;
	char	*new_str;

	new_len = ft_strlen(*str) + 1;
	new_str = ft_calloc(new_len + 1, sizeof(char));
	new_str = ft_insert_o_copy(*str, new_str, c, position);
	free(*str);
	*str = new_str;
}
