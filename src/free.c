/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:18:11 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/11 17:17:56 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear_pipe(t_pipe *this)
{
	if (this->path)
		ft_free_split(this->path);
	// TODO check if this->end is on the heap
	if (this->infile)
		free(this->infile);
	if (this->outfile)
		free(this->outfile);
	free(this);
}

/*
** free_data does not free(data) because it's on the stack (not on the heap).
*/

void	free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->pipe)
		ft_lstclear_pipe(data->pipe);
	if (data->cmd)
		ft_lstclear_cmd(data->cmd);
	if (data->env_lst)
		ft_lstclear_env(data->env_lst);
	data->line = 0;
	data->pipe = 0;
	data->cmd = 0;
	data->env_lst = 0;
}

/*
** err_free properly frees all memory that has been allocated with malloc
** and exits the program with exit_status 1.
*/

void	err_free(char *msg, t_data *data, char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	free_data(data);
	write(2, "Error: ", 7);
	if (msg && *msg)
		write(2, msg, ft_strlen(msg));
	else
		write(2, MALLOC_ERROR, ft_strlen(MALLOC_ERROR));
	exit(EXIT_FAILURE);
}