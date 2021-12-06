/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/06 12:17:54 by llalba           ###   ########.fr       */
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

static void	finish_pipe(t_data *data, t_pipe *pipe, pid_t pid)
{
	int	i;
	pid_t	tmp; // FIXME
	int	wstatus;

	i = -1;
	close_all_fd(pipe);
	while (++i < pipe->nb_pipe - 1)
	{
		printf("pid avant wait : %d\n", pid); // FIXME
		fflush(stdout); // FIXME
		tmp = waitpid(0, &wstatus, 0);
		printf("pid apres : %d\n", tmp); // FIXME
		fflush(stdout); // FIXME
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
	finish_pipe(data, pipe, pid);
}
