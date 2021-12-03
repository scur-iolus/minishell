/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:26:32 by llalba            #+#    #+#             */
/*   Updated: 2021/12/03 12:30:58 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	even_nb_of_quote_marks(char *line)
{
	long	apostrophes;
	long	quote_marks;

	apostrophes = 0;
	quote_marks = 0;
	while (*line)
	{
		if ((*line) == '\\' || (*line) == ';')
		{
			ft_error(INVALID_CHAR);
			return (0);
		}
		else if ((*line) == '\'' && quote_marks % 2 == 0)
			apostrophes++;
		else if ((*line) == '\"' && apostrophes % 2 == 0)
			quote_marks++;
		line++;
	}
	if (apostrophes % 2 || quote_marks % 2)
	{
		ft_error(ODD_NB);
		return (0);
	}
	return (1);
}

/*
** On the heap: line
*/

static void	copy_n_char(t_data *data, size_t len_without_0)
{
	char	*new;
	size_t	i;

	i = 0;
	new = ft_calloc(len_without_0 + 1, sizeof(char));
	if (!new)
		err_free(MALLOC_ERROR, data, 0);
	while (i < len_without_0)
	{
		new[i] = (data->line)[i];
		i++;
	}
	free(data->line);
	(data->line) = new;
}

/*
** On the heap: line
*/

void	remove_comment(t_data *data)
{
	size_t	len;
	t_bool	is_between_apostrophes;

	len = 0;
	is_between_apostrophes = 0;
	if ((data->line)[0] != '#')
	{
		while ((data->line)[len])
		{
			if ((data->line)[len] == '\'')
				is_between_apostrophes = !is_between_apostrophes;
			if ((data->line)[len] == '#' && (data->line)[len - 1] == ' ' && \
			!is_between_apostrophes)
			{
				len--;
				break ;
			}
			len++;
		}
	}
	copy_n_char(data, len);
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

/*
** On the heap: line, data->env_lst
*/

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
