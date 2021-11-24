/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:07:17 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/17 17:15:34 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_unset(t_data *data, char **cmd)
{
	int i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] == '-')
		{
			ft_putstr_fd("unset: -", 1);
			ft_putstr_fd(cmd[i][1], 1);
			ft_putstr_fd("': invalid option\n", 1);
			return (2);
		}
		if (error_var_name(cmd[i]))
		{
			ft_putstr_fd("unset: ", 1);
			ft_putstr_fd(cmd[i], 1);
			ft_putstr_fd(": not a valid identifier\n", 1);
			return (127);
		}
	}
	i = 0;
	while (cmd[++i])
		pop_out_list(data, cmd[i]);
	return (0);
}

static t_env	*find_previous_var_env(t_data *data, char *var_name)
{
	t_env	*temp;
	t_env	*previous;
	int		i;

	previous = NULL;
	temp = data->env_lst;
	i = -1;
	while(temp)
	{
		if (!ft_strcmp(var_name, temp->var))
			return (previous);
		previous = temp;
		temp = temp->next;
	}
	return(NULL);
}

void	pop_out_list_env(t_data *data, char *line) // a tester
{
	t_env *temp;
	t_env *previous;

	temp = find_var_env(data, line);
	previous = find_previous_var_env(data, line);
	if (!temp)
		return ;
	else if (!previous && !temp->next) //cas ou il est seul dans la liste
		delete_one_env_var(temp); //free temp --> du coup la list chaines sera a null
	else if (!previous && temp->next) // cas ou c est le premier
	{
		data->env_lst = temp->next;
		delete_one_env_var(temp);
	}
	else if (previous && !temp->next)
		delete_one_env_var(temp);
	else if (previous && temp->next)
	{
		previous->next = temp->next;
		delete_one_env_var(temp);
	}
}
