/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/30 17:51:46 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	do_cmd(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->cmd_nb == 1) // peut faire directement la redirection
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
	while(list)
	{
		i++;
		if (list->outfile)
			break;
		list = list->next;
	}
	return (i);
}

static void	finish_pipe(t_data *data, t_pipe *pipe)  //FIXME : mieux gerer les exit status retour
{
	int	i;
	int	status;

	i = -1;
	close_all_fd(pipe);
	while (++i < pipe->nb_pipe - 1)
	{
		waitpid(0 ,&status , 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else
			ft_error("Something goes wrong"); // NOTA BENE : si jamais le programme fini sans passer par un return ou un exit, est ce que c'est la ou on met le retour du signal ?
	}
}

void	fork_creation(t_pipe *pipe, t_data *data)
{
	int		pid;
	int		x;
	t_cmd *list;

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
			ft_error("Fork Failed");
		if (pid == 0)
			do_cmd(data, pipe, list);
		list = list->next;
	}
	finish_pipe(data, pipe);
}
