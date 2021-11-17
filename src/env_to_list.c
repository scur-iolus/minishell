/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:11:57 by llalba            #+#    #+#             */
/*   Updated: 2021/11/17 14:14:16 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Depuis init_env, On the heap: line, data->env_lst
*/

char	*get_var_name(t_data *data, char *str)//CHECKED
{
	size_t	i;
	char	*var_name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var_name = (char *) ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		err_free(MALLOC_ERROR, data, 0, 0);
	i = 0;
	while (str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	str[i] = '\0';  // Petit rajout
	return (var_name);
}

/*
** Depuis init_env, On the heap: line, data->env_lst
*/

char	*get_var_value(t_data *data, char *str)//CHECKED
{
	size_t	j;
	char	*var_value;

	while (str && *str && *str != '=')
		str++;
	if (str && *str == '=')
		var_value = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	else
		var_value = (char *)ft_calloc(1, sizeof(char));
	if (!var_value)
		err_free(MALLOC_ERROR, data, 0, 0);
	if (str && *str)
		str++;
	j = 0;
	while (str && *str)
	{
		var_value[j] = *str;
		str++;
		j++;
	}
	str[j] = '\0';
	return (var_value);
}

/*
** On the heap: line
*/

t_env	*init_env(t_data *data, char **env)//CHECKED
{
	size_t	i;
	t_env	*head;
	t_env	*new;
	char	*equals_sign;

	if (!env)
		return (0);
	i = 0;
	head = 0;
	while (env[i])
	{
		equals_sign = ft_strchr(env[i], '=');
		if (equals_sign)
		{
			new = ft_lstnew_env();
			if (!new)
				err_free(MALLOC_ERROR, data, 0, 0);
			env_add_front(&head, new);
			new->var = get_var_name(data, env[i]);
			new->value = get_var_value(data, env[i]);
			new->is_env = 1;
		}
		i++;
	}
	return (head);
}
