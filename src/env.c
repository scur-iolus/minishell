/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:19:35 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/17 17:02:04 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_data *data, char **cmd)
{
	t_env *temp;
	int i;

	i = 0;
	while (cmd[++i])
		if (check_argument_ft_env(cmd[i]))
			return 127;
	if (cmd[1][0] == "-")
		return (0);
	temp  = data->env_lst;
	while (temp)
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
	i = 0;
	while (cmd[++i])
		ft_putstr_fd(cmd[i], 1);
	return (0);
}

int	check_argument_ft_env(char **cmd)
{
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			if(cmd[1][1])
			{
				ft_putstr_fd("env: invalid option -- '", 1);
				ft_putstr_fd(cmd[1][1], 1);
				ft_putstr_fd("'", 1);
				return (1)
			}
		}
		else
		{
			if (!check_equal_sign(cmd[1]))
			{
				ft_putstr_fd("env: '", 1);
				ft_putstr_fd(cmd[1], 1);
				ft_putstr_fd("': ", 1);
				ft_putstr_fd("No such file or directory", 1);
				return (1)
			}
		}
	}
	return (0);
}
