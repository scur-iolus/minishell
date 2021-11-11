/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:18:10 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/11 18:16:41 by llalba           ###   ########.fr       */
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
	data->end = ft_calloc(argc - 2 - data->flag_hd, sizeof(int *));
	while (++i < (argc - 2 - data->flag_hd))
	{
		data->end[i] = ft_calloc(2, sizeof(int));
		pipe(data->end[i]);
		if (pipe(data->end[i]) == -1)
			error_pipe(data);
	}
}
