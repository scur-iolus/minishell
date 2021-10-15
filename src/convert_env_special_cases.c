/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_special_cases.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:09:25 by llalba            #+#    #+#             */
/*   Updated: 2021/10/15 18:43:43 by llalba           ###   ########.fr       */
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

static	void	add_exit_stt(char **out, char *line, size_t *pos, t_data *data)
{
	char		c;
	int			highest_pow;
	long long	tmp;

	tmp = data->exit_status;
	highest_pow = get_highest_pow(tmp);
	if (!tmp)
		add_one_char(out, line, pos, '0');
	while (highest_pow + 1)
	{
		c = (tmp / power(10, (unsigned long) highest_pow)) + '0';
		add_one_char(out, line, pos, c);
		tmp -= (c - '0') * power(10, (unsigned long) highest_pow);
		highest_pow--;
	}
}

short	add_special_case(char **output, char *line, size_t *pos, t_data *data)
{
	if (line[*pos] == '?')
		add_exit_stt(output, line, pos, data);
	else
	{
		add_one_char(output, line, pos, '$');
		if (line[*pos] == '.')
			add_one_char(output, line, pos, '.');
		else if (line[*pos] == '$')
			add_one_char(output, line, pos, '$');
	}
	if (line[*pos] == '.' || line[*pos] == '$' || line[*pos] == '?')
		return (1);
	return (0);
}