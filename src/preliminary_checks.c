/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:26:32 by llalba            #+#    #+#             */
/*   Updated: 2021/11/10 14:35:04 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	split_n_join(char **line)
{
	char	**line_split;
	char	**tmp;
	size_t	i;

	line_split = ft_split(*line, '"');
	if (!line_split)
		exit(1); // TODO: malloc fail, free et exit à coder proprement
	free(*line);
	tmp = line_split;
	i = 1;
	while (line_split[0] && line_split[i])
	{
		*line = ft_strjoin(line_split[0], line_split[i]);
		if (!(*line))
			exit(1); // TODO: malloc fail, free et exit à coder proprement
		free(line_split[0]);
		free(line_split[i]);
		line_split[0] = *line;
		i++;
	}
	free(tmp);
}

static void	remove_quotation_marks(char **line)
{
	size_t	i;
	long	apostrophes;

	i = 0;
	apostrophes = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'')
			apostrophes++;
		else if ((*line)[i] == '\"' && apostrophes % 1 == 0)
			(*line)[i] = ';';
		i++;
	}
	if (ft_strchr(*line, (int) '\"'))
		split_n_join(line);
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == ';')
			(*line)[i] = '\"';
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
			return (0);
		else if ((*line) == '\'' && quote_marks % 2 == 0)
			apostrophes++;
		else if ((*line) == '\"' && apostrophes % 2 == 0)
			quote_marks++;
		line++;
	}
	if (apostrophes % 2 == 1 || quote_marks % 2 == 1)
	{
		write(1, ODD_NB_APOSTROPHES, ft_strlen(ODD_NB_APOSTROPHES));
		return (0);
	}
	return (1);
}

/*
** Sur la heap: line
*/

static void	copy_n_char(t_data *data, size_t len_without_0)// CHECKED
{
	char	*new;
	size_t	i;

	i = 0;
	new = ft_calloc(len_without_0 + 1, sizeof(char));
	if (!new)
		err_free(0, data, 0, 0);
	while (i < len_without_0)
	{
		new[i] = (data->line)[i];
		i++;
	}
	free(data->line);
	(data->line) = new;
}

/*
** Sur la heap: line
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
