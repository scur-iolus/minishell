/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:52 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/23 15:05:57 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_all_fd(t_pipe *pipe)
{
	int	i;

	i = -1;
	while (++i < pipe->nb_pipe)
	{
		if (i != pipe->nb_pipe)
			close(pipe->end[i][0]);
		if (i != 0)
			close(pipe->end[i][1]);
	}
}

void	close_fd_first_process(t_pipe *pipe)
{
	int	i;
	int	j;

	i = -1;
	while (++i < pipe->nb_pipe)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == pipe->i + 1 && j == 1)
				continue ;
			close(pipe->end[i][j]);
		}
	}
}

void	close_fd_middle_process(t_pipe *pipe)
{
	int	i;
	int	j;

	i = -1;
	while (++i < pipe->nb_pipe)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == pipe->i + 1 && j == 1)
				continue ;
			else if (i == pipe->i && j == 0)
				continue ;
			close(pipe->end[i][j]);
		}
	}
}

void	close_fd_last_process(t_pipe *pipe)
{
	int	i;
	int	j;

	i = -1;
	while (++i < pipe->nb_pipe)
	{
		j = -1;
		while (++j < 2)
		{
			if (i == pipe->i && j == 0)
				continue ;
			close(pipe->end[i][j]);
		}
	}
}
