/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:33:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/03 14:51:26 by llalba           ###   ########.fr       */
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

	data->exit_status = 0;
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

	save_stdout = dup(1);
	save_stdin = dup(0);
	open_infile_and_heredoc(cmd);
	if (cmd->outfile) // si outfile
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	launch_built_in(data, cmd);
	if (cmd->outfile)
		dup2(save_stdout, STDOUT_FILENO);
	if (cmd->infile)
		dup2(save_stdin, STDIN_FILENO);
}

void	launch_built_in(t_data *data, t_cmd *cmd)
{
	if (!ft_strcmp("echo", cmd->cmd[0])) //FONCTION OK
		data->exit_status = ft_echo(cmd->cmd);
	else if (!ft_strcmp("cd", cmd->cmd[0])) //FONCTION OK
		data->exit_status = ft_cd(data, cmd->cmd);
	else if (!ft_strcmp("pwd", cmd->cmd[0])) //FONCTION OK
		data->exit_status = ft_pwd(data, cmd->cmd);
	else if (!ft_strcmp("export", cmd->cmd[0])) //FONCTION OK
		data->exit_status = ft_export(data, cmd->cmd);
	else if (!ft_strcmp("unset", cmd->cmd[0])) //FONCTION OK
		data->exit_status = ft_unset(data, cmd->cmd);
	else if (!ft_strcmp("env", cmd->cmd[0])) //FONCTION OK
		data->exit_status = ft_env(data, cmd->cmd);
	else if (!ft_strcmp("exit", cmd->cmd[0])) //FONCTION OK
		ft_exit(data, cmd->cmd);
}


// Si une commande commence par/ alors pas la peine de chercher le path
// il faut le acces pour voir si c est valide
// si valide alors on fait la commmande
// une commande pourra etre comme suit :
// execve(/bin/ls,{cmd[0] = /bin/ls , cmd[i...] = option, arguments...}, char **env);

// en gros  quand on trouve une commande qui commence par / ou ../ on le split normalement
// si ./ alors on doit enlever le ./ pour faire le access
