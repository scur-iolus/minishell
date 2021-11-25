/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:36:27 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/24 15:25:18 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export(t_data *data, char **cmd) // faut il afficher la liste en ordre alphabetique ??
{
	int i;

	i = 0;
	if (!cmd[1])
		print_export(data);
	else
		while(cmd[++i])
		{
			if (error_var_name(cmd[i]))
			{
				ft_putstr_fd("export: '", 1);
				ft_putstr_fd(cmd[i], 1);
				ft_putstr_fd("': not a valid identifier\n", 1);
				return (1);
				continue ;
			}
			put_in_env_export(data, cmd, i);
			return (0);
		}
}

void	put_in_env_export(t_data *data, char **cmd, int i)
{
	t_env *new;

	new = find_var_env(data, cmd[i]);
	if(!new)
		new = (t_env *) ft_calloc(1, sizeof(t_env));
	if(!new)
		ft_error(MALLOC_ERROR);
	if (new)
	{
		free(new->var);
		free(new->value);
	}
	new->equal_sign = check_equal_sign(cmd[i]);
	new->var = get_var_name(data, cmd[i]);
	new->value = get_var_value(data, cmd[i]);
	new->is_env = check_is_env(cmd[i]);
	env_add_front(&data->env_lst, new);
}

int	check_equal_sign(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

int	error_var_name(char *line)
{
	int i;

	i = -1;
	if(ft_isdigit(line[0]))
		return(1);
	while(line[++i] && line[i]!= '=')
	{
		if (!ft_isalnum(line[i]))
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
