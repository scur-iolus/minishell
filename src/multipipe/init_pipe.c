/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:18:10 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/03 12:36:53 by llalba           ###   ########.fr       */
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
		ft_putstr_fd("ERROR: Malloc Failed", 2);
		return (1); //FIXME : est ce qu on doit tout fermer ?? Je pense qu il faut aller au prochain readline
	}
	while (++i < nb_pipe)
	{
		pipes->end[i] = ft_calloc(2, sizeof(int));
		if (!pipes->end[i])
		{
			ft_putstr_fd("ERROR: Malloc Failed", 2);
			return (1); //FIXME : est ce qu on doit tout fermer ??
		}
		pipe(pipes->end[i]);
		if (pipe(pipes->end[i]) == -1)
		{
			ft_putstr_fd("ERROR: Pipe Failed", 2);
			return (1); //FIXME : est ce qu on doit tout fermer ??
		}
	}
	return (0);
}

int	init_pipe_struct(t_data *data)
{
	data->pipe.end = NULL;
	data->pipe.cmd_nb = 0;
	data->pipe.cmd_len = 0;
	data->pipe.i = 0;
	data->pipe.nb_pipe = ft_lstsize(data->cmd) + 1;
	if (init_pipe(data->pipe.nb_pipe, data, &data->pipe))
		return (1);
	return (0);
}
