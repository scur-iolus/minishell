/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:34:50 by llalba            #+#    #+#             */
/*   Updated: 2021/11/09 11:27:21 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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