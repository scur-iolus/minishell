/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:34:50 by llalba            #+#    #+#             */
/*   Updated: 2021/12/02 15:48:12 by llalba           ###   ########.fr       */
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

	i = 0;
	while ((data->line)[i])
	{
		ptr = (data->line) + i;
		if ((*ptr == '<' || *ptr == '>') && i && *(ptr - 1) != ' ' && \
		*(ptr - 1) != '<' && *(ptr - 1) != '>')
		{
			if (!ft_str_insert(&data->line, " ", i))
				err_free(MALLOC_ERROR, data, 0);
		}
		if ((*ptr == '<' || *ptr == '>') && *(ptr + 1) && \
		*(ptr + 1) != ' ' && *(ptr + 1) != '<' && *(ptr + 1) != '>')
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

void	deduplicate_spaces(t_data *data)
{
	char	*new;
	char	*str;
	size_t	i;
	t_bool	was_space;

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
}

/*
** On the heap: line, data->env_lst
*/

t_bool	valid_start_end(char *line)
{
	char	last_char;

	if (*line == 0)
		return (1);
	last_char = line[ft_strlen(line) - 1];
	if (last_char != '<' && last_char != '>' && last_char != '|')
	{
		if (line[0] == '|')
		{
			ft_error(START_CHAR_ERR);
			return (0);
		}
		return (1);
	}
	else
	{
		ft_error(END_CHAR_ERR);
		return (0);
	}
}
