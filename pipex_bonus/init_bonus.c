/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:52:55 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/09/28 12:05:52 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

t_data	*init_struct(int argc, char **argv, int flag_hd)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->cmd = NULL;
	data->path = NULL;
	data->list = NULL;
	data->end = NULL;
	data->i = -1;
	data->argc = argc;
	data->flag_hd = flag_hd;
	if (data->flag_hd)
	{
		data->here_doc = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (data->here_doc < 0 || data->outfile < 0)
			error_opening_file(data);
	}
	else
	{
		data->infile = open(argv[1], O_RDONLY);
		data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->infile < 0 || data->outfile < 0)
			error_opening_file(data);
	}
	return (data);
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
