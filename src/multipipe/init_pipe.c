/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:18:10 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/17 12:28:33 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_struct(t_pipe *pipe)
{
	pipe->path = NULL; //split du path
	pipe->end = NULL;
	pipe->infile = NULL; // permet de recup le fd de l ouverture du infile //FIXME pas utile je pense
	pipe->outfile = NULL; // 										outfile // FIXME idem
	pipe->i = NULL;
	pipe->argc = NULL;
}

void	init_pipe(int argc, t_data *data)
{
	int	i;

	i = -1;
	data->end = ft_calloc(argc - 2 - data->flag_hd, sizeof(int *));
	while (++i < (argc - 2 - data->flag_hd))
	{
		data->end[i] = ft_calloc(2, sizeof(int));
		pipe(data->end[i]);
		if (pipe(data->end[i]) == -1)
			error_pipe(data);
	}
}
