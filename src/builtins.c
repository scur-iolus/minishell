/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/13 18:04:47 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_data *data)
{
	t_env *pwd_env;

	// s'il y a des arguments en plus du genre pwd bonjour alors --> pwd: too many arguments

	pwd_env = find_var_env(data, "PWD");
	ft_putstr_fd(pwd_env->value, 1);
}

void	ft_env(t_data *data)
{
	t_env *temp;

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

void	ft_exit(t_data *data)
{
	// s' il y a une commande apres le exit alors exit ne renvoie rien dans le stdin
	ft_putstr_fd("exit", 1);
	free_all_sucess(data);
}
