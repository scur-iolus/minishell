/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:26:32 by llalba            #+#    #+#             */
/*   Updated: 2021/12/02 21:32:15 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst
*/

void	remove_quotation_marks(t_data *data)
{
	secure_between_apo(data->line, '\'');
	if (ft_strchr(data->line, (int) '\"'))
		if (!ft_split_n_join(&(data->line), '\"'))
			err_free(MALLOC_ERROR, data, 0);
	replace_semicolon(data->line, '\"');
}

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
			ft_error(INVALID_CHAR_ERR);
			return (0);
		}
		else if ((*line) == '\'' && quote_marks % 2 == 0)
			apostrophes++;
		else if ((*line) == '\"' && apostrophes % 2 == 0)
			quote_marks++;
		line++;
	}
	if (apostrophes % 2 == 1 || quote_marks % 2 == 1)
	{
		ft_error(ODD_NB_APOSTROPHES);
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
