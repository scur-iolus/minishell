/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:34:50 by llalba            #+#    #+#             */
/*   Updated: 2021/12/03 12:31:24 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst
*/

void	space_before_after_chevron(t_data *data)
{
	size_t	i;
	char	*ptr;
	t_bool	between_q;

	i = 0;
	while ((data->line)[i])
	{
		between_q = quote_status(data->line, i);
		ptr = (data->line) + i;
		if (!between_q && (*ptr == '<' || *ptr == '>') && i \
			&& *(ptr - 1) != ' ' && *(ptr - 1) != '<' && *(ptr - 1) != '>')
		{
			if (!ft_str_insert(&data->line, " ", i))
				err_free(MALLOC_ERROR, data, 0);
		}
		if (!between_q && (*ptr == '<' || *ptr == '>') \
			&& *(ptr + 1) && *(ptr + 1) != ' ' && *(ptr + 1) != '<' \
			&& *(ptr + 1) != '>')
		{
			if (!ft_str_insert(&data->line, " ", i + 1))
				err_free(MALLOC_ERROR, data, 0);
		}
		i++;
	}
}

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

/*
** On the heap: line, data->env_lst
*/

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

/*
** On the heap: line, data->env_lst
*/

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
** On the heap: line, data->env_lst
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
