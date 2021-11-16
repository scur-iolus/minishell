/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:14:54 by llalba            #+#    #+#             */
/*   Updated: 2021/11/16 15:39:05 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** free_data does not free(data) because it's on the stack (not on the heap).
*/

void	free_data(t_data *data)//CHECKED
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

void	free_everything(t_data *data, char *str, char **split)//CHECKED
{
	rl_clear_history();
	if (str)
		free(str);
	if (split)
		ft_free_split(split);
	free_data(data);
}

/*
** err_free properly frees all memory that has been allocated with malloc
** and exits the program with exit_status 1.
*/

void	err_free(char *msg, t_data *data, char *str, char **split)//CHECKED
{
	free_everything(data, str, split);
	if (msg && *msg)
		ft_error(msg);
	else
		ft_error(MALLOC_ERROR);
	exit(EXIT_FAILURE);
}
