/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:18:10 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/07 11:00:25 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_pipe(int nb_pipe, t_data *data, t_pipe *pipes)
{
	int	i;

	i = -1;
	pipes->end = ft_calloc(nb_pipe, sizeof(int *));
	if (!pipes->end)
	{
		ft_error(MALLOC_ERROR);
		return (1);
	}
	while (++i < nb_pipe)
	{
		pipes->end[i] = ft_calloc(2, sizeof(int));
		if (!pipes->end[i])
		{
			ft_error(MALLOC_ERROR);
			return (1);
		}
		if (pipe(pipes->end[i]) == -1)
		{
			ft_error("Failed to create pipe\n");
			return (1);
		}
	}
	return (0);
}

int	init_pipe_struct(t_data *data)
{
	data->pipe.end = NULL;
	data->pipe.cmd_nb = 0;
	data->pipe.i = 0;
	data->pipe.nb_pipe = ft_lstsize(data->cmd) + 1;
	if (init_pipe(data->pipe.nb_pipe, data, &data->pipe))
		return (1);
	return (0);
}
