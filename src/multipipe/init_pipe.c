/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:18:10 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/11 18:08:55 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_struct(t_pipe *pipe)
{
	pipe->path = NULL; //split du path
	pipe->end = NULL;
	pipe->infile = NULL; // permet de recup le fd de l ouverture du infile
	pipe->outfile = NULL; // 										outfile
	pipe->i = NULL;
	pipe->argc = NULL;
}

void	init_pipe(int argc, t_data *data)
{
	int	i;

	i = -1;
	data->end = malloc(sizeof(int *) * (argc - 2 - data->flag_hd));
	while (++i < (argc - 2 - data->flag_hd))
	{
		data->end[i] = malloc(sizeof(int) * 2);
		pipe(data->end[i]);
		if (pipe(data->end[i]) == -1)
			error_pipe(data);
	}
}
