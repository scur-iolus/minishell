/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:33:21 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/17 17:45:56 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_cmd(t_data *data, t_cmd *cmd)
{
	if (strcmp("echo", cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_echo(data, cmd->cmd);
	else if (strcmp("cd", cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_cd(data, cmd->cmd);
	else if (strcmp("pwd", cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_pwd(data);
	else if (strcmp("export", cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_export(data, cmd->cmd);
	else if (strcmp("unset", cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_unset(data, cmd->cmd);
	else if (strcmp("env", cmd->cmd[0])) //NOTA BENE : ok mais a tester
		ft_env(data, cmd->cmd);
	// else if (strcmp("exit", cmd->cmd[0])) //
	// 	ft_exit(data, cmd->cmd);
}
