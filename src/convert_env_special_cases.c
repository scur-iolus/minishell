/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_special_cases.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:09:25 by llalba            #+#    #+#             */
/*   Updated: 2021/11/11 17:51:57 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static unsigned long long	power(unsigned long x, unsigned long y)
{
	unsigned long		i;
	unsigned long long	result;

	i = 0;
	result = 1;
	while (i < y)
	{
		result *= x;
		i++;
	}
	return (result);
}

static int	get_highest_pow(long long n)
{
	int	y;

	y = 0;
	while (n / power(10, (unsigned long) y))
		y++;
	return (y - 1);
}

/*
** On the heap: line, data->env_lst, output
*/

static short	add_exit_stt(t_data *data, char **output, size_t *pos)
{
	char		c;
	int			highest_pow;
	long long	tmp;
	short		success;

	success = 1;
	tmp = data->exit_status;
	highest_pow = get_highest_pow(tmp);
	if (!tmp)
		success = ft_str_insert_char(output, '0', ft_strlen(*output));
	while (success && tmp && highest_pow + 1)
	{
		c = (tmp / power(10, (unsigned long) highest_pow)) + '0';
		success *= ft_str_insert_char(output, c, ft_strlen(*output));
		tmp -= (c - '0') * power(10, (unsigned long) highest_pow);
		highest_pow--;
	}
	return (success);
}

/*
** On the heap: line, data->env_lst, output
**
** $$ reste $$ (on ne doit pas gérer l'affichage du PID)
** $. reste $.
** $ESPACE reste $ESPACE
** $? devient le dernier exit_status
*/

short	special_cases(t_data *data, char **output, size_t *pos)
{
	short	success;

	if (data->line[*pos] == '?')
		success = add_exit_stt(data, output, pos);
	else if (data->line[*pos] == ' ')
		success = ft_str_insert_str(output, "$ ", ft_strlen(*output));
	else if (data->line[*pos] == '$')
		success = ft_str_insert_str(output, "$$", ft_strlen(*output));
	else if (data->line[*pos] == '.')
		success = ft_str_insert_str(output, "$.", ft_strlen(*output));
	if (!success)
		err_free(0, data, *output, 0);
	else if (data->line[*pos] == '.' || data->line[*pos] == '$' || \
		data->line[*pos] == '?')
		return (1);
	else
		return (0);
}