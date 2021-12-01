/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:33:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/01 11:25:19 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_data *data)
{
	short	vertical_bar;

	vertical_bar = ft_strrchr(data->line, '|');
	if (!vertical_bar && data->cmd->cmd == 0)
		return ;
	if (!vertical_bar && is_built_in(data))
	{
		make_one_built_in(data);
	}
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

void	make_one_built_in(t_data *data)
{
	printf("bonjour tu veux quoi comme commande ?\n"); // NOTA BENE
	open_infile_and_heredoc(data->cmd);
	if (data->cmd->outfile) // si outfile
	{
		dup2(data->cmd->outfile, STDOUT_FILENO);
		close(data->cmd->outfile);
	}
	if (!ft_strcmp("echo", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_echo(data, data->cmd->cmd);
	else if (!ft_strcmp("cd", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_cd(data, data->cmd->cmd);
	else if (!ft_strcmp("pwd", data->cmd->cmd[0])) //FONCTION OK
		ft_pwd(data);
	else if (!ft_strcmp("export", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_export(data, data->cmd->cmd);
	else if (!ft_strcmp("unset", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_unset(data, data->cmd->cmd);
	else if (!ft_strcmp("env", data->cmd->cmd[0])) //FONCTION OK
		ft_env(data, data->cmd->cmd);
	//rajouter exit
}
