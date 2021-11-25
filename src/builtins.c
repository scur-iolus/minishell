/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/25 09:54:40 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_data *data)
{
	t_env *pwd_env;

	pwd_env = find_var_env(data, "PWD");
	ft_putstr_fd(pwd_env->value, 1);
	return (0);
}

void	ft_exit(t_data *data, char *str, char **split, long long exit_status)
{
	if (exit_status < -2147483646 || exit_status > 2147483646)
	{
		ft_error(INVALID_STATUS);
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	if (split)
		ft_free_split(split);
	free_everything(data, str);
	exit((int)exit_status);
}
