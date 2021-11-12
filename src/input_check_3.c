/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:05:02 by llalba            #+#    #+#             */
/*   Updated: 2021/11/12 15:36:47 by llalba           ###   ########.fr       */
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
	short	fail;

	fail = 0;
	if (!max_n_consecutive_c(2, '<', data->line))
		fail = 1;
	if (!max_n_consecutive_c(2, '>', data->line))
		fail = 1;
	if (!max_n_consecutive_c(1, '|', data->line))
		fail = 1;
	if (fail)
		ft_error(INVALID_CHAR_ERR);
	return (fail);
}

/*
** On the heap: line, data->env_lst
** In bash, note that '>< test' raises an error but that '<> test' doesn't...
*/

short	invalid_suite(t_data *data)//CHECKED
{
	unsigned long long	i;
	char				prev_char;

	i = 0;
	prev_char = 0;
	while ((data->line)[i])
	{
		if ((data->line)[i] == '<' && prev_char == '>')
		{
			ft_error(INVALID_CHAR_ERR);
			return (1);
		}
		prev_char = (data->line)[i];
		i++;
	}
	return (0);
}