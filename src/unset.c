/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:07:17 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/03 18:53:51 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*find_previous_var_env(t_data *data, char *var_name)
{
	t_env	*temp;
	t_env	*previous;
	int		i;

	previous = NULL;
	temp = data->env_lst;
	i = -1;
	while (temp)
	{
		if (!ft_strcmp(var_name, temp->var))
			return (previous);
		previous = temp;
		temp = temp->next;
	}
	return (NULL);
}

static void	pop_out_list_env(t_data *data, char *line) // a tester
{
	t_env	*temp;
	t_env	*previous;

	temp = find_var_env(data, line);
	previous = find_previous_var_env(data, line);
	if (!temp)
		return ;
	else if (!previous && !temp->next)
		delete_one_env_var(temp);
	else if (!previous && temp->next)
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

int	ft_unset(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] == '-')
		{
			ft_putstr_fd("unset: -", 1);
			ft_putchar_fd(cmd[i][1], 1);
			ft_putstr_fd("': invalid option\n", 1);
			return (2);
		}
		if (error_var_name(cmd[i]))
		{
			ft_putstr_fd("unset: `", 1);
			ft_putstr_fd(cmd[i], 1);
			ft_putstr_fd("\': not a valid identifier\n", 1);
			return (127);
		}
	}
	i = 0;
	while (cmd[++i])
		pop_out_list_env(data, cmd[i]);
	return (0);
}

int	error_var_name(char *line)
{
	int	i;

	i = -1;
	if (!line[0])
		return(1);
	if (ft_isdigit(line[0]))
		return (1);
	while (line[++i] && line[i] != '=')
	{
		if (!ft_is_var_name(line[i]))
			return (1);
	}
	return (0);
}

int	ft_is_var_name(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}
