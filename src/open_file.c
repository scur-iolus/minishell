/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:14:43 by llalba            #+#    #+#             */
/*   Updated: 2021/11/25 13:20:10 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static short	close_previous(t_cmd *head, char *file, short opening)//CHECKED
{
	int	fail;

	fail = 0;
	if (head->infile && opening == ONE_LEFT)
		fail = close(head->infile);
	else if (head->outfile && (opening == ONE_RIGHT || opening == TWO_RIGHT))
		fail = close(head->outfile);
	if (fail == -1)
	{
		ft_error(FAILED_TO_CLOSE);
		return (0);
	}
	return (1);
}

short	open_file(t_cmd *head, char *file, short opening)//CHECKED
{
	int	fd;

	if (!close_previous(head, file, opening))
		return (0);
	fd = 0;
	if (opening == ONE_RIGHT)
		fd = open (file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (opening == TWO_RIGHT)
		fd = open (file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (opening == ONE_LEFT)
		fd = open (file, O_RDONLY);
	if (fd == -1)
	{
		ft_error(FILE_NOT_FOUND);
		return (0);
	}
	if (opening == ONE_LEFT)
		head->infile = fd;
	if (opening == ONE_RIGHT || opening == TWO_RIGHT)
		head->outfile = fd;
	return (1);
}