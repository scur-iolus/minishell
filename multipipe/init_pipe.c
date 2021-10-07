/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:18:10 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/07 12:22:47 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_struct(int argc, char **argv, t_data *data)
{
	if (data->in == 1)
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
