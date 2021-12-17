/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:07:17 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/17 14:25:09 by llalba           ###   ########.fr       */
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

static void	pop_out_list_env(t_data *data, char *line)
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

static void	print_error_unset(char **cmd, int i, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("unset: -", 1);
		ft_putchar_fd(cmd[i][1], 1);
		ft_putstr_fd("': invalid option\n", 1);
	}
	if (flag == 1)
	{
		ft_putstr_fd("unset: `", 1);
		ft_putstr_fd(cmd[i], 1);
		ft_putstr_fd("\': not a valid identifier\n", 1);
	}
}

static int	unset_while(int i, char **cmd)
{
	if (cmd[i][0] == '-')
	{
		print_error_unset(cmd, i, 0);
		return (2);
	}
	if (error_var_name(cmd[i]))
	{
		print_error_unset(cmd, i, 1);
		return (127);
	}
	if (check_equal_sign(cmd[i]))
	{
		print_error_unset(cmd, i, 1);
		return (1);
	}
	return (0);
}

int	ft_unset(t_data *data, char **cmd)
{
	int	i;
	int	ret;
	int	status;

	status = 0;
	ret = 0;
	i = 0;
	while (cmd[++i])
	{
		status = unset_while(i, cmd);
		if (status && !ret)
			ret = status;
		if (!status)
			pop_out_list_env(data, cmd[i]);
	}
	return (ret);
}
