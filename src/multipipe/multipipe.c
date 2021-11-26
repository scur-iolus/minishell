/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/26 19:20:18 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fork_creation(t_pipe *pipe, t_data *data)
{
	int	pid;
	int	x;
	t_cmd *list;

	list = data->cmd;
	x = -1;
	while (++x < pipe->nb_pipe - 1 && list)
	{
		pipe->cmd_nb++; // a reset lors d'une redirection
		pipe->i++;
		if (pipe->cmd_len == 0)
			pipe->cmd_len = len_before_redirection(list); // a reset lors d'une redirection pour recalculer le nb de commande
		pid = fork();
		if (pid < 0)
			ft_putstr_fd("ERROR: Fork Failed", 1);
		if (pid == 0)
			do_cmd(data, &pipe, list);
		list = list->next;
	}
}

void	do_cmd(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->cmd_nb == 1) // peut faire directement la redirection
		first_process(data, pipe, cmd);
	else if (pipe->cmd_nb > 1 && pipe->cmd_nb < pipe->cmd_len)
		middle_process(data, pipe, cmd);
	else if (pipe->cmd_nb > 1 && pipe->cmd_nb == pipe->cmd_len)
		last_process(data, pipe, cmd);
}

int	len_before_redirection(t_cmd *cmd)
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

void	command_failed(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	write(2, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
	err_free(CMD_NOT_FOUND, data, 0);
}


