/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:17:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/15 17:54:21 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_var_name(char *line)
{
	int	i;

	i = -1;
	if (!line[0])
		return (1);
	if (ft_isdigit(line[0]))
		return (1);
	while (line[++i] && line[i] != '=')
	{
		if (!ft_is_var_name(line[i]))
			return (1);
	}
	return (0);
}

int	ft_is_var_name(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}
