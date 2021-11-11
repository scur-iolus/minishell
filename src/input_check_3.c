/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:05:02 by llalba            #+#    #+#             */
/*   Updated: 2021/11/11 17:24:14 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst
*/

static short	max_n_consecutive_c(long long n, char c, char *str)//CHECKED
{
	long long	count;

	while(*str)
	{
		if (*str == c)
			count++;
		else
			count = 0;
		if (count > n)
			return (0);
		str++;
	}
	return (1);
}

/*
** On the heap: line, data->env_lst
*/

short	too_many_chevrons_o_pipes(t_data *data)//CHECKED
{
	if (!max_n_consecutive_c(2, '<', data->line))
		return (1);
	if (!max_n_consecutive_c(2, '>', data->line))
		return (1);
	if (!max_n_consecutive_c(1, '|', data->line))
		return (1);
	return (0);
}