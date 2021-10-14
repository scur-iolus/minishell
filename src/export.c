/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:36:27 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/14 15:00:22 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export(t_data *data, char *line) // changer avec la line du parsing // faut il afficher la liste en ordre alphabetique ??
// changer le fd sur lequel on travaille avec les pipes
{
	t_env *new;

	if (error_var_name(line))
	{
		ft_putstr_fd("export: '", 1);
		ft_putstr_fd(get_var_name(line), 1);
		ft_putstr_fd("': not a valid identifier", 1);
		data->exit_status = 1;
		return ;
	}
	if (line)
	{
		new = find_var_env(data, line);
		if(!new)
			new = (t_env *) malloc(sizeof(t_env));
		if(!new)
			free_all_failure(data);
		new->var = get_var_name(line);
		new->value = get_var_value(line); // s accorder sur le parsing
		new->is_env = check_is_env(line);
		env_add_front(data->env_lst, new);
	}
	else
		print_export(data);
}

int	error_var_name(char *line)
{
	int i;

	i = -1;
	if(ft_isdigit(line[0]))
		return(1);
	while(line[++i] && line[i]!= '=')
	{
		if (!ft_is_alnum(line[i]))
			return (1);
	}
	return (0);
}

int	check_is_env(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '=')
			return (1);
	}
	return (0);
}

void	print_export(t_data *data)
{
	t_env *temp;

	temp  = data->env_lst;
	print_env_with_export_layout(data);
	while(temp)
	{
		if (!temp->is_env)
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

void	print_env_with_export_layout(t_data *data)
{
	t_env *temp;

	temp  = data->env_lst;
	while(temp)
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
