/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/16 15:39:13 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_data *data)
{
	t_env *pwd_env;

	data->exit_status = 0;
	pwd_env = find_var_env(data, "PWD");
	ft_putstr_fd(pwd_env->value, 1);
}

void	ft_env(t_data *data)
{
	t_env *temp;

	data->exit_status = 0;
	temp  = data->env_lst;
	while(temp)
	{
		if (temp->is_env == 1)
		{
			ft_putstr_fd(temp->var, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		temp = temp->next;
	}
}

/*
** S' il y a une commande apres le exit alors exit ne renvoie rien dans le stdin
*/

void	ft_exit(t_data *data, char *str, char **split, long long exit_status)
{
	if (exit_status < 0 || exit_status > 2147483646)
	{
		ft_error(INVALID_STATUS);
		return ;
	}
	if (data->cmd->next == 0)
		ft_putstr_fd("exit", 1);
	free_everything(data, str, split);
	exit((int)exit_status);
}
