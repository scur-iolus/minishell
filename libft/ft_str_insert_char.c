/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:40:26 by llalba            #+#    #+#             */
/*   Updated: 2021/11/11 18:53:02 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_proceed(char *old, char **new, char c, size_t position)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (old[i] || i <= position)
	{
		if (i == j && i == position)
		{
			(*new)[j] = c;
		}
		else
		{
			(*new)[j] = old[i];
			i++;
		}
		j++;
	}
}

short	ft_str_insert_char(char **str, char c, size_t position)
{
	size_t	old_len;
	size_t	new_len;
	char	*new_str;

	if (!(*str))
		return (0);
	old_len = ft_strlen(*str);
	if (position > old_len)
		return (0);
	new_len = old_len + 1;
	new_str = ft_calloc(new_len + 1, sizeof(char));
	if (!new_str)
		return (0);
	ft_proceed(*str, &new_str, c, position);
	free(*str);
	*str = new_str;
	return (1);
}
