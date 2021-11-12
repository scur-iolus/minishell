/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:26:32 by llalba            #+#    #+#             */
/*   Updated: 2021/11/12 15:39:53 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst
*/

static void	split_n_join(t_data *data, char c)//CHECKED
{
	char	**l_split;
	size_t	i;

	l_split = ft_split(data->line, c);
	if (!l_split)
		err_free(MALLOC_ERROR, data, 0, 0);
	free(data->line);
	i = 0;
	data->line = (char *)ft_calloc(1, sizeof(char));
	if (!data->line)
	{
		ft_free_split(l_split);
		err_free(MALLOC_ERROR, data, 0, 0);
	}
	while (l_split[i])
	{
		if (!ft_str_insert(&(data->line), l_split[i], ft_strlen(data->line)))
		{
			ft_free_split(l_split);
			err_free(MALLOC_ERROR, data, 0, 0);
		}
		i++;
	}
	ft_free_split(l_split);
}

/*
** On the heap: line, data->env_lst
*/

void	remove_quotation_marks(t_data *data)//CHECKED
{
	size_t	i;
	long	apostrophes;

	i = 0;
	apostrophes = 0;
	while ((data->line)[i])
	{
		if ((data->line)[i] == '\'')
			apostrophes++;
		else if ((data->line)[i] == '\"' && apostrophes % 2 == 1)
			(data->line)[i] = ';';
		i++;
	}
	if (ft_strchr(data->line, (int) '\"'))
		split_n_join(data, '\"');
	i = 0;
	while ((data->line)[i])
	{
		if ((data->line)[i] == ';')
			(data->line)[i] = '\"';
		i++;
	}
}

short	even_nb_of_quote_marks(char *line)// CHECKED
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

static void	copy_n_char(t_data *data, size_t len_without_0)// CHECKED
{
	char	*new;
	size_t	i;

	i = 0;
	new = ft_calloc(len_without_0 + 1, sizeof(char));
	if (!new)
		err_free(MALLOC_ERROR, data, 0, 0);
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

void	remove_comment(t_data *data)// CHECKED
{
	size_t	len;
	short	is_between_apostrophes;

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
