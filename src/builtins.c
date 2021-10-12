/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/12 11:56:43 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_data *data)
{
	t_env *pwd_env;

	pwd_env = find_var_env(data, "PWD");
	ft_putstr_fd(pwd_env->value, 1);
}

void	ft_export(t_data *data, t_cmd *cmd)
{

}

void	ft_env(t_data *data, t_cmd *cmd)
{
	
}
