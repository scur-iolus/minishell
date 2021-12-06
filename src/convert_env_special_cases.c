/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_special_cases.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:09:25 by llalba            #+#    #+#             */
/*   Updated: 2021/12/06 11:36:44 by llalba           ###   ########.fr       */
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

static t_bool	add_exit_status(t_data *data, char **output)
{
	char		c;
	int			highest_pow;
	long long	tmp;
	t_bool		success;

	success = 1;
	tmp = data->exit_status;
	if (!tmp)
	{
		success = ft_str_insert(output, "0", ft_strlen(*output));
		return (success);
	}
	highest_pow = get_highest_pow(tmp);
	while (success && highest_pow + 1)
	{
		c = (tmp / power(10, (unsigned long) highest_pow)) + '0';
		success *= ft_str_insert(output, &c, ft_strlen(*output));
		tmp -= (c - '0') * power(10, (unsigned long) highest_pow);
		highest_pow--;
	}
	return (success);
}

/*
** $$ reste $$ (on ne doit pas gérer l'affichage du PID)
** $. reste $.
** $ESPACE reste $ESPACE
** $? devient le dernier exit_status
*/

t_bool	env_special_cases(t_data *data, char **output, size_t *pos)
{
	t_bool	success;

	if (data->line[*pos] == '?')
		success = add_exit_status(data, output);
	else if (data->line[*pos] == ' ')
		success = ft_str_insert(output, "$ ", ft_strlen(*output));
	else if (data->line[*pos] == '$')
		success = ft_str_insert(output, "$$", ft_strlen(*output));
	else if (data->line[*pos] == '.')
		success = ft_str_insert(output, "$.", ft_strlen(*output));
	else if (data->line[*pos] == '\0')
		success = ft_str_insert(output, "$", ft_strlen(*output));
	if (!success)
		err_free(MALLOC_ERROR, data, *output);
	if (data->line[*pos] != '\0')
		return (1);
	return (0);
}
