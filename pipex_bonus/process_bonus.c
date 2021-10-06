/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 13:53:01 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/09/28 15:00:46 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	first_process(t_data *data, int argc, t_list *list, char **env)
{
	close_fd_first_process(argc, data);
	if (data->flag_hd)
	{
		data->here_doc = open("here_doc", O_RDONLY, 0644);
		if (data->here_doc < 0)
			error_opening_file(data);
		dup2(data->here_doc, STDIN_FILENO);
		close(data->here_doc);
	}
	else
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	dup2(data->end[data->i + 1][1], STDOUT_FILENO);
	close(data->end[data->i + 1][1]);
	if (list->cmd_path == NULL || execve(list->cmd_path, list->cmd, env) == -1)
		error_command(data);
}

void	middle_process(t_data *data, int argc, t_list *list, char **env)
{
	close_fd_middle_process(argc, data);
	dup2(data->end[data->i][0], STDIN_FILENO);
	dup2(data->end[data->i + 1][1], STDOUT_FILENO);
	close(data->end[data->i + 1][1]);
	close(data->end[data->i][0]);
	if (list->cmd_path == NULL || execve(list->cmd_path, list->cmd, env) == -1)
		error_command(data);
}

void	last_process(t_data *data, int argc, t_list *list, char **env)
{
	close_fd_last_process(argc, data);
	dup2(data->end[data->i][0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->end[data->i][0]);
	close(data->outfile);
	if (list->cmd_path == NULL || execve(list->cmd_path, list->cmd, env) == -1)
		error_command(data);
}

void	parent_process(t_data *data, int argc, int pid)
{
	int	i;

	i = -1;
	close_all_fd(argc, data);
	while (++i < argc - 3 - data->flag_hd)
		waitpid(pid, NULL, 0);
	free_all_success(data);
}
