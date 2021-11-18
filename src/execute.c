/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:33:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/18 19:05:34 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_data *data)
{
	int i;

	i = ft_lstsize(data->cmd);
	if (i == 1)
		make_one_cmd(data);
	//else
	// ca part en gros pipex
}

void	make_one_cmd(t_data *data)
{
	if (strcmp("echo", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_echo(data, data->cmd->cmd);
	else if (strcmp("cd", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_cd(data, data->cmd->cmd);
	else if (strcmp("pwd", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_pwd(data);
	else if (strcmp("export", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_export(data, data->cmd->cmd);
	else if (strcmp("unset", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_unset(data, data->cmd->cmd);
	else if (strcmp("env", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_env(data, data->cmd->cmd);
	// else if (strcmp("exit", data->cmd->cmd[0])) //
	// 	ft_exit(data, data->cmd->cmd);
	else
		if ((data->cmd->cmd_path == NULL || execve (data->cmd->cmd_path, data->cmd->cmd, data->env) == -1))
			ft_putstr_fd("ERROR : Something goes wrong", 2); // FIXME : Check si on doit tout arreter si une commande foire
}

// void	multi_pipe(t_data *data)
// {
// 	t_pipe pipe;

// 	data->pipe = init_struct_pipe(&pipe); // OK
// 	init_pipe(argc, data); //pipe initialisé en fonction de la longueur de la liste chainées commande // X process + 1
// 	pipex(argc, data, env);
// }
