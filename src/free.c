/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:14:54 by llalba            #+#    #+#             */
/*   Updated: 2021/12/15 17:52:42 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_lstclear_pipe(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (data->cmd)
		j = ft_lstsize(data->cmd) + 1;
	if (data->pipe.end)
	{
		while (i < j)
		{
			free(data->pipe.end[i]);
			i++;
		}
		free(data->pipe.end);
		data->pipe.end = NULL;
	}
}

void	free_pipe(t_data *data)
{
	if (data->pipe.end)
		ft_lstclear_pipe(data);
}

/*
** free_everything does not free(data) because it's on the stack
** (not on the heap).
*/

void	free_everything(t_data *data, char *str)
{
	rl_clear_history();
	if (str)
		free(str);
	if (data->env)
		ft_free_split(data->env);
	if (data->path)
		ft_free_split(data->path);
	if (data->line)
		free(data->line);
	free_pipe(data);
	if (data->cmd)
		ft_lstclear_cmd(data->cmd);
	if (data->env_lst)
		ft_lstclear_env(data->env_lst);
	data->line = 0;
	data->cmd = 0;
	data->env_lst = 0;
}

/*
** err_free properly frees all memory that has been allocated with malloc
** and exits the program with exit_status 1.
*/

void	err_free(char *msg, t_data *data, char *str)
{
	free_everything(data, str);
	if (msg && *msg)
		ft_error(msg);
	else
		ft_error(MALLOC_ERROR);
	exit(EXIT_FAILURE);
}

void	err_free_command_not_found(char *msg, t_data *data, char *str)
{
	free_everything(data, str);
	if (msg && *msg)
		ft_error(msg);
	else
		ft_error(MALLOC_ERROR);
	exit(127);
}
