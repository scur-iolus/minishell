/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/15 17:43:33 by fmonbeig         ###   ########.fr       */
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

void	ft_exit(t_data *data, int n)
{
	data->exit_status = 0;
	// s' il y a une commande apres le exit alors exit ne renvoie rien dans le stdin
	ft_putstr_fd("exit", 1);
	free_all_sucess(data); // faire un free all success special avec un exit n
	exit(n);
}
