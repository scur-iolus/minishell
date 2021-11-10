/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:40:26 by llalba            #+#    #+#             */
/*   Updated: 2021/11/10 14:05:46 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void ft_proceed(char *str1, char *str2, char *new, size_t position)
{
	size_t	str1_i;
	size_t	new_i;

	str1_i = 0;
	new_i = 0;
	while (str1[str1_i] || str1_i <= position)
	{
		if (str1_i == new_i && str1_i == position)
		{
			while (*str2)
			{
				new[new_i] = *str2;
				new_i++;
				str2++;
			}
		}
		else
		{
			str2[new_i] = str1[str1_i];
			str1_i++;
			new_i++;
		}
	}
}

short	ft_str_insert_str(char **str1, char *str2, size_t position, size_t len)
{
	size_t	new_len;
	char	*new_str;

	new_len = ft_strlen(*str1) + len;
	new_str = ft_calloc(new_len + 1, sizeof(char));
	if (!new_str)
		return (0);
	ft_proceed(*str1, str2, new_str, position);
	free(*str1);
	*str1 = new_str;
	return (1);
}
