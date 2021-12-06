/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:34:50 by llalba            #+#    #+#             */
/*   Updated: 2021/12/06 11:40:39 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	ft_strlen_wth_duplicates_sp(char *str)
{
	size_t	i;
	t_bool	was_space;

	i = 0;
	was_space = 0;
	while (*str)
	{
		if (!was_space || (was_space && *str != ' '))
			i++;
		if (*str == ' ')
			was_space = 1;
		else
			was_space = 0;
		str++;
	}
	return (i);
}

void	deduplicate_spaces(t_data *data)
{
	char	*new;
	char	*str;
	size_t	i;
	t_bool	was_space;

	secure_between(data->line, ' ', ';', FALSE);
	new = ft_calloc(ft_strlen_wth_duplicates_sp(data->line) + 1, sizeof(char));
	if (!new)
		err_free(MALLOC_ERROR, data, 0);
	str = data->line;
	i = 0;
	was_space = 0;
	while (*str)
	{
		if (!was_space || (was_space && *str != ' '))
			new[i++] = *str;
		if (*str == ' ')
			was_space = 1;
		else
			was_space = 0;
		str++;
	}
	free(data->line);
	data->line = new;
	secure_between(data->line, ' ', ';', TRUE);
}

static t_bool	max_n_consecutive_c(long long n, char c, char *str)
{
	long long	count;
	size_t		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!quote_status(str, i) && str[i] == c)
			count++;
		else
			count = 0;
		if (count > n)
			return (0);
		i++;
	}
	return (1);
}

t_bool	too_many_chevrons_o_pipes(t_data *data)
{
	t_bool	fail;

	fail = 0;
	if (!max_n_consecutive_c(2, '<', data->line))
		fail = 1;
	if (!max_n_consecutive_c(2, '>', data->line))
		fail = 1;
	if (!max_n_consecutive_c(1, '|', data->line))
		fail = 1;
	if (fail)
		ft_error(INVALID_CHAR);
	return (fail);
}

/*
** In bash, note that '>< test' raises an error but that '<> test' doesn't...
*/

t_bool	invalid_suite(t_data *data)
{
	unsigned long long	i;
	char				prev_char;

	i = 0;
	prev_char = 0;
	while ((data->line)[i])
	{
		if (!quote_status(data->line, i) && (data->line)[i] == '<' && \
			prev_char == '>')
		{
			ft_error(INVALID_CHAR);
			return (1);
		}
		prev_char = (data->line)[i];
		i++;
	}
	return (0);
}
