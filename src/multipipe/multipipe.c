/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/22 15:20:12 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	multi_pipe(t_data *data)
{
	t_pipe pipe;

	if (init_pipe_struct(&pipe, data))
	{
		if (pipe.end)
			ft_lstclear_pipe(pipe.end, data);
		return ;
	}
	if	(fork_creation(&pipe, data))
	{
		if (pipe.end)
			ft_lstclear_pipe(pipe.end, data);
		return ;
	}
	if (pipe.end)
		ft_lstclear_pipe(pipe.end, data);
}

int	fork_creation(t_pipe *pipe, t_data *data)
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
		{
			ft_putstr_fd("ERROR: Fork Failed", 2);
			return (1);
		}
		if (pid == 0)
			do_cmd(data, &pipe, list);
		list = list->next;
	}
	return (0);
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

void	do_cmd(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->cmd_nb == 1) // peut faire directement la redirection
		first_process(data, pipe, cmd);
	else if (pipe->cmd_nb > 1 && pipe->cmd_nb < pipe->cmd_len)
		middle_process(data, pipe, cmd);
	else if (pipe->cmd_nb > 1 && pipe->cmd_nb == pipe->cmd_len)
		last_process(data, pipe, cmd);
}

void	make_one_cmd(t_data *data) // ici il vaut mieux partir direct sur de la création de fd et sur le multipipe
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
			exit (1); // est ce qu'on doit free la heap dans l'enfant ??
		}
	}
}

void	first_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	close_fd_first_process(argc, data); // A custom
	if (pipe->cmd_len == 1) // ouverture et fermeture quand c est la fin du pipe
	{
		if (cmd->outfile)
		{
			dup2(cmd->outfile, STDOUT_FILENO);
			close(cmd->outfile);
		}
		else
		{
			dup2(pipe->end[pipe->i + 1][1], STDOUT_FILENO);
			close(pipe->end[pipe->i + 1][1]);
		}
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

// void	middle_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
// {
// 	close_fd_middle_process(argc, data);
// 	dup2(data->end[data->i][0], STDIN_FILENO);
// 	dup2(data->end[data->i + 1][1], STDOUT_FILENO);
// 	close(data->end[data->i + 1][1]);
// 	close(data->end[data->i][0]);
// 	if (list->cmd_path == NULL || execve(list->cmd_path, list->cmd, env) == -1)
// 		error_command(data);
// }

// void	last_process(t_data *data, t_pipe *pipe, t_cmd *cmd)
// {
// 	close_fd_last_process(argc, data);
// 	dup2(data->end[data->i][0], STDIN_FILENO);
// 	dup2(data->outfile, STDOUT_FILENO);
// 	close(data->end[data->i][0]);
// 	close(data->outfile);
// 	if (list->cmd_path == NULL || execve(list->cmd_path, list->cmd, env) == -1)
// 		error_command(data);
// }


// 0	Entrée standard	STDIN_FILENO	stdin
// 1	Sortie standard	STDOUT_FILENO	stdout


//write end[1]
// read end[0]
