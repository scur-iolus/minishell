/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/23 15:05:33 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	multi_pipe(t_data *data)
{
	if (!init_pipe_struct(&pipe, data))
		fork_creation(&pipe, data);
	free_pipe(data, &pipe);
	close_all_fd(&pipe);
}

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
	ft_putstr_fd(cmd->cmd[0], 1);
	ft_putstr_fd(" : command not found", 1);
	free_pipe(data, pipe);
	free_data(data);
	exit (1);
}

void	first_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->cmd_nb == pipe->cmd_len)
		close_all_fd(pipe);
	close_fd_first_process(pipe); // A custom si outfile alors fermer plus de chose
	if (cmd->outfile) // si outfile
		dup_outfile(cmd);
	else if (pipe->cmd_nb < pipe->cmd_len) // ou si pas dernier
	{
		dup2(pipe->end[pipe->i + 1][1], STDOUT_FILENO);
		close(pipe->end[pipe->i + 1][1]);
	}
	open_infile_and_heredoc(data, pipe, cmd);

	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}

void	middle_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	close_fd_middle_process(pipe);
	dup2(pipe->end[pipe->i][0], STDIN_FILENO);
	dup2(pipe->end[pipe->i + 1][1], STDOUT_FILENO);
	close(pipe->end[pipe->i + 1][1]);
	close(pipe->end[pipe->i][0]);
	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}

void	last_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	close_fd_last_process(pipe);
	if (cmd->outfile) // si outfile
		dup_outfile(cmd);
	dup2(pipe->end[pipe->i][0], STDIN_FILENO);
	close(pipe->end[pipe->i][0]);
	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}


// 0	Entrée standard	STDIN_FILENO	stdin
// 1	Sortie standard	STDOUT_FILENO	stdout


//write end[1]
// read end[0]
