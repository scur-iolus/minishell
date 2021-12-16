/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:11:57 by llalba            #+#    #+#             */
/*   Updated: 2021/12/16 18:24:05 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_name(t_data *data, char *str)
{
	size_t	i;
	char	*var_name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var_name = (char *) ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		err_free(MALLOC_ERROR, data, 0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}

char	*get_var_value(t_data *data, char *str)
{
	size_t	j;
	char	*var_value;

	while (str && *str && *str != '=')
		str++;
	if (str && *str && *str == '=')
		var_value = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	else
		var_value = (char *)ft_calloc(1, sizeof(char));
	if (!var_value)
		err_free(MALLOC_ERROR, data, 0);
	if (str && *str)
		str++;
	j = 0;
	while (str && *str)
	{
		var_value[j] = *str;
		str++;
		j++;
	}
	return (var_value);
}

t_env	*init_env(t_data *data, char **env)
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
				err_free(MALLOC_ERROR, data, 0);
			env_add_front(&head, new);
			new->var = get_var_name(data, env[i]);
			new->value = get_var_value(data, env[i]);
			new->is_env = 1;
		}
		i++;
	}
	return (head);
}
