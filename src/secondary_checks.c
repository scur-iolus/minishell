/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:34:50 by llalba            #+#    #+#             */
/*   Updated: 2021/10/19 16:44:35 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

short	file_not_found(char *line)
{
	while (*line)
	{
		// TODO detecter nom de fichier, essayer de l'ouvrir
		line++;
	}
	return (0);
}

short	invalid_end_of_line(char *line)
{
	char	last_char;

	last_char = line[ft_strlen(line) - 1];
	if (last_char != '<' && last_char != '>' && last_char != '|')
		return (0);
	else
	{
		write(2, INVALID_CHAR_ERR, ft_strlen(INVALID_CHAR_ERR));
		return (1);
	}
}