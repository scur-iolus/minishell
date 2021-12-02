/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:24:06 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/02 20:45:37 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_data *data)
{
	t_env	*temp;

	temp = data->env_lst;
	print_env_with_export_layout(data);
	while (temp)
	{
		if (!temp->is_env)
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(temp->var, 1);
			if (temp->equal_sign)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(temp->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		temp = temp->next;
	}
}

void	print_env_with_export_layout(t_data *data)
{
	t_env	*temp;

	temp = data->env_lst;
	while (temp)
	{
		if (temp->is_env)
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(temp->var, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		temp = temp->next;
	}
}
