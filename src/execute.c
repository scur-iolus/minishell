/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:33:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/24 11:58:56 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_data *data)
{
	int i;

	i = ft_lstsize(data->cmd);
	if (i == 1 && is_built_in(data))
		make_one_built_in(data);
	// else
	// 	multi_pipe(data);
}


int		is_built_in(t_data *data)
{
	if (strcmp("echo", data->cmd->cmd[0]))
		return (1);
	else if (strcmp("cd", data->cmd->cmd[0]))
		return (1);
	else if (strcmp("pwd", data->cmd->cmd[0]))
		return (1);
	else if (strcmp("export", data->cmd->cmd[0]))
		return (1);
	else if (strcmp("unset", data->cmd->cmd[0]))
		return (1);
	else if (strcmp("env", data->cmd->cmd[0]))
		return (1);
	else if (strcmp("exit", data->cmd->cmd[0]))
		return (1);
	else
		return(0);
}

void	make_one_built_in(t_data *data)
{
	if (data->cmd->outfile)
	{
		dup2(data->cmd->outfile, STDOUT_FILENO);
		close(data->cmd->outfile);
	}
	if (!strcmp("echo", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_echo(data, data->cmd->cmd);
	else if (!strcmp("cd", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_cd(data, data->cmd->cmd);
	else if (!strcmp("pwd", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_pwd(data);
	else if (!strcmp("export", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_export(data, data->cmd->cmd);
	else if (!strcmp("unset", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_unset(data, data->cmd->cmd);
	else if (!strcmp("env", data->cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_env(data, data->cmd->cmd);
	//rajouter exit
}
