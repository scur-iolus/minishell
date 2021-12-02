/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:40:26 by llalba            #+#    #+#             */
/*   Updated: 2021/12/02 15:34:24 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void ft_proceed(char *str1, char *str2, char **new, size_t position)
{
	size_t	str1_i;
	size_t	new_i;

	str1_i = 0;
	new_i = 0;
	while (str1[str1_i] || *str2)
	{
		if (*str2 && str1_i == position)
		{
			while (*str2)
			{
				(*new)[new_i] = *str2;
				new_i++;
				str2++;
			}
		}
		else
		{
			(*new)[new_i] = str1[str1_i];
			str1_i++;
			new_i++;
		}
	}
}

t_bool	ft_str_insert(char **str1, char *str2, size_t position)
{
	size_t	len_str1;
	size_t	len_str2;
	char	*new_str;

	if (!(*str1) || !(*str2))
		return (0);
	len_str2 = ft_strlen(str2);
	if (!len_str2)
		return (1);
	len_str1 = ft_strlen(*str1);
	if (position > len_str1)
		return (0);
	new_str = ft_calloc(len_str1 + len_str2 + 1, sizeof(char));
	if (!new_str)
		return (0);
	ft_proceed(*str1, str2, &new_str, position);
	free(*str1);
	*str1 = new_str;
	return (1);
}
