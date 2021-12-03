/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:03:00 by llalba            #+#    #+#             */
/*   Updated: 2021/12/03 11:10:56 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_remove_char(char **str, size_t char_id)
{
	size_t	new_len;
	size_t	j;
	size_t	k;
	char	*new;

	new_len = ft_strlen(*str) - 1;
	new = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (!new)
		return (0);
	j = 0;
	k = 0;
	while ((*str)[j])
	{
		if (j != char_id)
		{
			new[k] = (*str)[j];
			k++;
		}
		j++;
	}
	free(*str);
	*str = new;
	return (1);
}
