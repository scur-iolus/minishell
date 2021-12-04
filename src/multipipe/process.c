/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:20:04 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/04 14:41:58 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	first_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->cmd_nb == pipe->cmd_len)
		close_all_fd(pipe);
	close_fd_first_process(pipe);
	open_infile_and_heredoc(cmd);
	if (cmd->outfile)
		dup_outfile(cmd, pipe);
	else if (pipe->cmd_nb < pipe->cmd_len)
	{
		dup2(pipe->end[pipe->i + 1][1], STDOUT_FILENO);
		close(pipe->end[pipe->i + 1][1]);
	}
	if (cmd->ok == 0)
		command_failed_because_of_file_opening(data);
	if (is_built_in(cmd->cmd))
	{
		launch_built_in(data, cmd);
		free_everything(data, 0);
		exit(data->exit_status);
	}
	// if (access(cmd->cmd_path, X_OK))
	// 	err_free_command_not_found(FILE_NOT_FOUND, data, 0);
	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}

void	middle_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	close_fd_middle_process(pipe);
	dup2(pipe->end[pipe->i][0], STDIN_FILENO);
	dup2(pipe->end[pipe->i + 1][1], STDOUT_FILENO);
	open_infile_and_heredoc(cmd);
	close(pipe->end[pipe->i + 1][1]);
	close(pipe->end[pipe->i][0]);
	if (cmd->ok == 0)
		command_failed_because_of_file_opening(data);
	if (is_built_in(cmd->cmd))
	{
		launch_built_in(data, cmd);
		free_everything(data, 0);
		exit(data->exit_status);
	}
	// if (access(cmd->cmd_path, X_OK))
	// 	err_free_command_not_found(FILE_NOT_FOUND, data, 0);
	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}

void	last_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	close_fd_last_process(pipe);
	if (cmd->outfile)
		dup_outfile(cmd, pipe);
	dup2(pipe->end[pipe->i][0], STDIN_FILENO);
	open_infile_and_heredoc(cmd);
	close(pipe->end[pipe->i][0]);
	if (cmd->ok == 0)
		command_failed_because_of_file_opening(data);
	if (is_built_in(cmd->cmd))
	{
		launch_built_in(data, cmd);
		free_everything(data, 0);
		exit(data->exit_status);
	}
	// if (access(cmd->cmd_path, X_OK))
	// 	err_free_command_not_found(FILE_NOT_FOUND, data, 0);
	if ((cmd->cmd_path == NULL ||
				execve (cmd->cmd_path, cmd->cmd, data->env) == -1))
		command_failed(data, pipe, cmd);
}


// 0	Entrée standard	STDIN_FILENO	stdin
// 1	Sortie standard	STDOUT_FILENO	stdout


//write end[1]
// read end[0]
