/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:34:50 by llalba            #+#    #+#             */
/*   Updated: 2021/11/09 16:23:31 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	space_before_after_chevron(char **line)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while ((*line)[i])
	{
		ptr = (*line) + i;
		if ((*ptr == '<' || *ptr == '>') && i && *(ptr - 1) != ' ' && \
		*(ptr - 1) != '<' && *(ptr - 1) != '>')
		{
			ft_str_insert(line, ' ', i);
		}
		if ((*ptr == '<' || *ptr == '>') && *(ptr + 1) && \
		*(ptr + 1) != ' ' && *(ptr + 1) != '<' && *(ptr + 1) != '>')
		{
			ft_str_insert(line, ' ', i + 1);
		}
		i++;
	}
}

static size_t	ft_strlen_wth_duplicates_spaces(char *str)
{
	size_t	i;
	short	was_space;

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

void	deduplicate_spaces(char **line)
{
	char	*new;
	char	*str;
	size_t	i;
	short	was_space;

	new = ft_calloc(ft_strlen_wth_duplicates_spaces(*line) + 1, sizeof(char));
	if (!new)
		exit(1); // FIXME error de malloc a gerer proprement
	str = *line;
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
	free(*line);
	*line = new;
}

short	consecutive_chevrons_o_pipes(char *line)
{
	short	already_one;

	already_one = 0;
	while (*line)
	{
		if (!already_one && (*line == '<' || *line == '>' || *line == '|'))
			already_one = !already_one;
		if (already_one && *line != ' ' && *line != '<' || \
		*line != '>' || *line != '|')
			already_one = !already_one;
		if (already_one && (*line == '<' || *line == '>' || *line == '|'))
			return (1);
		line++;
	}
	return (0);
}

short	valid_start_end(char *line)
{
	char	last_char;

	last_char = line[ft_strlen(line) - 1];
	if (last_char != '<' && last_char != '>' && last_char != '|')
	{
		if (line[0] == '|')
		{
			write(2, START_CHAR_ERR1, ft_strlen(START_CHAR_ERR1));
			write(2, START_CHAR_ERR2, ft_strlen(START_CHAR_ERR2));
			return (0);
		}
		return (1);
	}
	else
	{
		write(2, INVALID_CHAR_ERR, ft_strlen(INVALID_CHAR_ERR));
		return (0);
	}
}