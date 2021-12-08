/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/08 16:58:59 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	do_cmd(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->cmd_nb == 1)
		first_process(data, pipe, cmd);
	else if (pipe->cmd_nb > 1 && pipe->cmd_nb < pipe->nb_pipe - 1)
		middle_process(data, pipe, cmd);
	else if (pipe->cmd_nb > 1 && pipe->cmd_nb == pipe->nb_pipe - 1)
		last_process(data, pipe, cmd);
}

static void	finish_pipe(t_data *data, t_pipe *pipe)
{
	int		i;
	pid_t	tmp;
	int		wstatus;

	i = -1;
	close_all_fd(pipe);
	while (++i < pipe->nb_pipe - 1)
	{
		tmp = waitpid(0, &wstatus, 0);
		update_exit_status(wstatus);
	}
}

void	fork_creation(t_pipe *pipe, t_data *data)
{
	pid_t	pid;
	int		x;
	t_cmd	*list;

	list = data->cmd;
	x = -1;
	while (++x < pipe->nb_pipe - 1 && list)
	{
		pipe->cmd_nb++;
		pipe->i++;
		pid = fork();
		if (pid < 0)
			ft_error(FORK_FAILED);
		if (pid == 0)
			do_cmd(data, pipe, list);
		list = list->next;
	}
	finish_pipe(data, pipe);
}
