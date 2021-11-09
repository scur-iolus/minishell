/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:07:17 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/09 11:38:19 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset(t_data *data, char *line)
{
	if (error_var_name(line))
	{
		ft_putstr_fd("unset: ", 1);
		ft_putstr_fd(line, 1);
		ft_putstr_fd(": invalid parameter name\n", 1);
		data->exit_status = 1; // exit status = 127 ?
		return ;
	}
	pop_out_list(data, line);
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
		delete_one_env_list(temp); //free temp --> du coup la list chaines sera a null
	else if (!previous && temp->next) // cas ou c est le premier
	{
		data->env_lst = temp->next;
		delete_one_env_list(temp);
	}
	else if (previous && !temp->next)
		delete_one_env_list(temp);
	else if (previous && temp->next)
	{
		previous->next = temp->next;
		delete_one_env_list(temp);
	}
}

t_env	*find_previous_var_env(t_data *data, char *var_name)
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
