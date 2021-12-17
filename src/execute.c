/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:33:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/17 11:09:29 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_bool	no_command(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->cmd != NULL)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	execute(t_data *data)
{
	char	*vertical_bar;

	vertical_bar = ft_strrchr(data->line, '|');
	if (!vertical_bar && data->cmd->cmd == 0)
		return ;
	if (no_command(data->cmd))
		return ;
	if (!vertical_bar && is_built_in(data->cmd->cmd))
		make_one_built_in(data, data->cmd);
	else
	{
		if (!init_pipe_struct(data))
			fork_creation(&data->pipe, data);
	}
}

int	is_built_in(char **cmd)
{
	if (!ft_strcmp("echo", cmd[0]))
		return (1);
	else if (!ft_strcmp("cd", cmd[0]))
		return (1);
	else if (!ft_strcmp("pwd", cmd[0]))
		return (1);
	else if (!ft_strcmp("export", cmd[0]))
		return (1);
	else if (!ft_strcmp("unset", cmd[0]))
		return (1);
	else if (!ft_strcmp("env", cmd[0]))
		return (1);
	else if (!ft_strcmp("exit", cmd[0]))
		return (1);
	else
		return (0);
}

void	make_one_built_in(t_data *data, t_cmd *cmd)
{
	int	save_stdout;
	int	save_stdin;
	int	fd[2];

	save_stdout = dup(1);
	save_stdin = dup(0);
	open_infile_and_heredoc(cmd, fd);
	if (cmd->outfile)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	launch_built_in(data, cmd);
	if (cmd->outfile)
		dup2(save_stdout, STDOUT_FILENO);
	if (cmd->infile || cmd->heredoc)
		dup2(save_stdin, STDIN_FILENO);
}

void	launch_built_in(t_data *data, t_cmd *cmd)
{
	if (!ft_strcmp("echo", cmd->cmd[0]))
		data->new_status = ft_echo(cmd->cmd);
	else if (!ft_strcmp("cd", cmd->cmd[0]))
		data->new_status = ft_cd(data, cmd->cmd);
	else if (!ft_strcmp("pwd", cmd->cmd[0]))
		data->new_status = ft_pwd(data, cmd->cmd);
	else if (!ft_strcmp("export", cmd->cmd[0]))
		data->new_status = ft_export(data, cmd->cmd);
	else if (!ft_strcmp("unset", cmd->cmd[0]))
		data->new_status = ft_unset(data, cmd->cmd);
	else if (!ft_strcmp("env", cmd->cmd[0]))
		data->new_status = ft_env(data, cmd->cmd);
	else if (!ft_strcmp("exit", cmd->cmd[0]))
		ft_exit(data, cmd->cmd);
}
