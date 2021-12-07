/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:36:27 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/07 18:29:09 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	put_in_env_export(t_data *data, char **cmd, int i)
{
	t_env	*new;
	char	*temp;

	temp = get_var_name(data, cmd[i]);
	new = find_var_env(data, temp);
	if (!new)
		new = (t_env *) ft_calloc(1, sizeof(t_env));
	if (!new)
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
	if (!new->value || !new->var)
		ft_error(MALLOC_ERROR);
	if (!find_var_env(data, temp))
		env_add_front(&data->env_lst, new);
	free(temp);
}

int	check_equal_sign(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

int	check_is_env(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '=')
			return (1);
	}
	return (0);
}

int	ft_export(t_data *data, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!cmd[1])
		print_export(data);
	else
	{
		while (cmd[++i])
		{
			if (error_var_name(cmd[i]) || cmd[i][0] == '=')
			{
				ft_putstr_fd("export: `", 1);
				ft_putstr_fd(cmd[i], 1);
				ft_putstr_fd("\': not a valid identifier\n", 1);
				j = 1;
				continue ;
			}
			put_in_env_export(data, cmd, i);
		}
		return (j);
	}
}
