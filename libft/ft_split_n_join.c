/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_n_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:22:41 by llalba            #+#    #+#             */
/*   Updated: 2021/12/02 21:24:43 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_split_n_join(char **str, char c)
{
	char	**l_split;
	size_t	i;

	l_split = ft_split(*str, c);
	if (!l_split)
		return (0);
	free(*str);
	i = 0;
	(*str) = (char *)ft_calloc(1, sizeof(char));
	if (!(*str))
	{
		ft_free_split(l_split);
		return (0);
	}
	while (l_split[i])
	{
		if (!ft_str_insert(str, l_split[i], ft_strlen(*str)))
		{
			ft_free_split(l_split);
			return (0);
		}
		i++;
	}
	ft_free_split(l_split);
	return (1);
}
