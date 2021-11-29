/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:33:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/29 10:37:48 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_data *data)
{
	int i;

	i = ft_lstsize(data->cmd);
	if (i == 1 && is_built_in(data))
		make_one_built_in(data, data->cmd);
	// else
	// {
	// 	if (!init_pipe_struct(&data->pipe, data))
	// 		fork_creation(&data->pipe, data);
	// }
}

int		is_built_in(t_data *data)
{
	printf("Bienvenue Built In %s \n", data->cmd->cmd[0]); // NOTA BENE
	if (!ft_strcmp("echo", data->cmd->cmd[0]))
		return (1);
	else if (!ft_strcmp("cd", data->cmd->cmd[0]))
		return (1);
	else if (!ft_strcmp("pwd", data->cmd->cmd[0]))
		return (1);
	else if (!ft_strcmp("export", data->cmd->cmd[0]))
		return (1);
	else if (!ft_strcmp("unset", data->cmd->cmd[0]))
		return (1);
	else if (!ft_strcmp("env", data->cmd->cmd[0]))
		return (1);
	else if (!ft_strcmp("exit", data->cmd->cmd[0]))
		return (1);
	else
	{
		printf("Ah non... tu n'est pas un Built In\n"); // NOTA BENE
		return(0);
	}
}

void	make_one_built_in(t_data *data, t_cmd *cmd)
{
	int	save_stdout;
	int	save_stdin;

	save_stdout = dup(1) ;
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
		data->exit_status = ft_pwd(data);
	else if (!ft_strcmp("export", cmd->cmd[0])) //NOTA BENE : ok mais a tester
		data->exit_status = ft_export(data, cmd->cmd);
	else if (!ft_strcmp("unset", cmd->cmd[0])) //NOTA BENE : ok mais a tester
		data->exit_status = ft_unset(data, cmd->cmd);
	else if (!ft_strcmp("env", cmd->cmd[0])) //FONCTION OK
		data->exit_status = ft_env(data, cmd->cmd);
	else if (!ft_strcmp("exit", cmd->cmd[0])) //FONCTION OK
		ft_exit2(data, cmd->cmd);
}
