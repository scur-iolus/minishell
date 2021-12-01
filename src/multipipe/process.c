/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:20:04 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/01 12:14:12 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	first_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->cmd_nb == pipe->cmd_len) // s'il n y a qu une seule commande
		close_all_fd(pipe);
	close_fd_first_process(pipe); // A custom si outfile alors fermer plus de chose
	open_infile_and_heredoc(cmd);
	if (cmd->outfile) // si outfile
		dup_outfile(cmd, pipe);
	else if (pipe->cmd_nb < pipe->cmd_len) // ou si pas dernier
	{
		dup2(pipe->end[pipe->i + 1][1], STDOUT_FILENO);
		close(pipe->end[pipe->i + 1][1]);
	}
	if (is_built_in(cmd->cmd))
	{
		launch_built_in(data, cmd);
		free_everything(data, 0);
		exit(data->exit_status);
	}
	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}

void	middle_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	close_fd_middle_process(pipe);
	open_infile_and_heredoc(cmd);
	dup2(pipe->end[pipe->i][0], STDIN_FILENO);
	dup2(pipe->end[pipe->i + 1][1], STDOUT_FILENO);
	close(pipe->end[pipe->i + 1][1]);
	close(pipe->end[pipe->i][0]);
	if (is_built_in(cmd->cmd))
	{
		launch_built_in(data, cmd);
		free_everything(data, 0);
		exit(data->exit_status);
	}
	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}

void	last_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	close_fd_last_process(pipe);
	open_infile_and_heredoc(cmd);
	if (cmd->outfile) // si outfile
		dup_outfile(cmd, pipe);
	dup2(pipe->end[pipe->i][0], STDIN_FILENO);
	close(pipe->end[pipe->i][0]);
	if (is_built_in(cmd->cmd))
	{
		launch_built_in(data, cmd);
		free_everything(data, 0);
		exit(data->exit_status);
	}
	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}


// 0	Entrée standard	STDIN_FILENO	stdin
// 1	Sortie standard	STDOUT_FILENO	stdout


//write end[1]
// read end[0]
