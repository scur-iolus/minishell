/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:08:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/09/28 12:10:01 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	close_all_fd(int argc, t_data *data)
{
	int	i;

	i = -1;
	while (++i < argc - 2 - data->flag_hd)
	{
		if (i != argc - 2 - data->flag_hd)
			close(data->end[i][0]);
		if (i != 0)
			close(data->end[i][1]);
	}
}

void	close_fd_first_process(int argc, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < argc - 2 - data->flag_hd)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == data->i + 1 && j == 1)
				continue ;
			close(data->end[i][j]);
		}
	}
}

void	close_fd_middle_process(int argc, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < argc - 2 - data->flag_hd)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == data->i + 1 && j == 1)
				continue ;
			else if (i == data->i && j == 0)
				continue ;
			close(data->end[i][j]);
		}
	}
}

void	close_fd_last_process(int argc, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < argc - 2 - data->flag_hd)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == data->i && j == 0)
				continue ;
			close(data->end[i][j]);
		}
	}
}
