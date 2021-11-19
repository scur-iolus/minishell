/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/19 18:09:42 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	multi_pipe(t_data *data) // pipex en cours de reconstruction
{
	t_pipe pipe;

	data->pipe = init_struct_pipe(&pipe); // OK
	take_path(data); // OK
	init_pipe(argc, data); //pipe initialisé en fonction de la longueur de la liste chainées commande // X process + 1
	pipex(argc, data, env);
	free_all_success(data);
}

// on ecrit sur end[1] et on lit sur end[0]
void	make_one_cmd(t_data *data) // ici il vaut mieux partir direct sur de la création de fd et sur le multipipe
{
	int pid;

	pid = fork();
	if (pid < 0)
		ft_putstr_fd("ERROR : Failed to make a fork", 2);
	if (pid == 0)
	{
		if (data->cmd->here_doc && !data->cmd->cmd[1]) // pour le heredoc en ecrit le char *str directement dans le fd

		else if (data->cmd->infile && !data->cmd->cmd[1])
		{
			dup2(data->cmd->infile, STDIN_FILENO);
			close(data->cmd->infile);
		}
		else if ((data->cmd->cmd_path == NULL ||
				execve (data->cmd->cmd_path, data->cmd->cmd, data->env) == -1))
		{
			ft_putstr_fd(data->cmd->cmd[0], 1);
			ft_putstr_fd(" : command not found", 1);
		}
	}
}

// void	first_process(t_data *data, int argc, t_list *list, char **env)
// {
// 	close_fd_first_process(argc, data);
// 	if (data->flag_hd)
// 	{
// 		data->here_doc = open("here_doc", O_RDONLY, 0644);
// 		if (data->here_doc < 0)
// 			error_opening_file(data);
// 		dup2(data->here_doc, STDIN_FILENO);
// 		close(data->here_doc);
// 	}
// 	else
// 	{
// 		dup2(data->infile, STDIN_FILENO);
// 		close(data->infile);
// 	}
// 	dup2(data->end[data->i + 1][1], STDOUT_FILENO);
// 	close(data->end[data->i + 1][1]);
// 	if (list->cmd_path == NULL || execve(list->cmd_path, list->cmd, env) == -1)
// 		error_command(data);
// }

// void	middle_process(t_data *data, int argc, t_list *list, char **env)
// {
// 	close_fd_middle_process(argc, data);
// 	dup2(data->end[data->i][0], STDIN_FILENO);
// 	dup2(data->end[data->i + 1][1], STDOUT_FILENO);
// 	close(data->end[data->i + 1][1]);
// 	close(data->end[data->i][0]);
// 	if (list->cmd_path == NULL || execve(list->cmd_path, list->cmd, env) == -1)
// 		error_command(data);
// }

// void	last_process(t_data *data, int argc, t_list *list, char **env)
// {
// 	close_fd_last_process(argc, data);
// 	dup2(data->end[data->i][0], STDIN_FILENO);
// 	dup2(data->outfile, STDOUT_FILENO);
// 	close(data->end[data->i][0]);
// 	close(data->outfile);
// 	if (list->cmd_path == NULL || execve(list->cmd_path, list->cmd, env) == -1)
// 		error_command(data);
// }
