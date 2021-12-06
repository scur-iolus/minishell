/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/06 12:06:04 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	do_cmd(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->cmd_nb == 1)
		first_process(data, pipe, cmd);
	else if (pipe->cmd_nb > 1 && pipe->cmd_nb < pipe->cmd_len)
		middle_process(data, pipe, cmd);
	else if (pipe->cmd_nb > 1 && pipe->cmd_nb == pipe->cmd_len)
		last_process(data, pipe, cmd);
}

static int	len_before_redirection(t_cmd *cmd)
{
	t_cmd	*list;
	int		i;

	i = 0;
	list = cmd;
	while (list)
	{
		i++;
		if (list->outfile)
			break ;
		list = list->next;
	}
	return (i);
}

static void	finish_pipe(t_data *data, t_pipe *pipe, pid_t pid)
{
	int	i;
	int	status;

	i = -1;
	close_all_fd(pipe);
	while (++i < pipe->nb_pipe - 1)
	{
		waitpid(pid, &status, 0);
		update_exit_status(status);
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
		if (pipe->cmd_len == 0)
			pipe->cmd_len = len_before_redirection(list);
		pid = fork();
		if (pid < 0)
			ft_error(FORK_FAILED);
		if (pid == 0)
			do_cmd(data, pipe, list);
		list = list->next;
	}
	finish_pipe(data, pipe, pid);
}
