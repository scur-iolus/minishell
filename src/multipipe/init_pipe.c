/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:18:10 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/22 14:52:26 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_pipe(int nb_pipe, t_data *data)
{
	int	i;

	i = -1;
	data->pipe->end = ft_calloc(nb_pipe, sizeof(int *));
	if (!data->pipe->end)
	{
		ft_putstr_fd("ERROR: Malloc Failed", 2);
		return (1);   //FIXME : est ce qu on doit tout fermer ?? Je pense qu il faut aller au prochain readline
	}
	while (++i < nb_pipe)
	{
		data->end[i] = ft_calloc(2, sizeof(int));
		if (!data->end[i])
		{
			ft_putstr_fd("ERROR: Malloc Failed", 2);
			return (1);   //FIXME : est ce qu on doit tout fermer ??
		}
		pipe(data->end[i]);
		if (pipe(data->end[i]) == -1)
		{
			ft_putstr_fd("ERROR: Malloc Failed", 2);
			return (1);   //FIXME : est ce qu on doit tout fermer ??
		}
	}
	return(0);
}

int	init_pipe_struct(t_pipe *pipe, t_data *data)
{
	pipe->end = NULL;
	pipe->cmd_nb = 0;
	pipe->cmd_len = 0;
	pipe->i = 0;
	pipe-> nb_pipe = ft_lstsize(data->cmd) + 1;
	if (init_pipe(pipe->nb_pipe, data))
		return (1);
	return (0);//pipe initialisé en fonction de la longueur de la liste chainées commande // X process + 1
}
