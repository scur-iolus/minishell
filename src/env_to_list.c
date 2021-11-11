/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:11:57 by llalba            #+#    #+#             */
/*   Updated: 2021/11/11 18:15:30 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_add_front(t_env **head, t_env *new)//CHECKED
{
	t_env	*temp;

	temp = *head;
	*head = new;
	new->next = temp;
}

/*
** Depuis init_env, On the heap: line, data->env_lst
*/

char	*get_var_name(t_data *data, char *str)//CHECKED
{
	size_t	i;
	char	*var_name;

	i = 0;
	while (str[i] != '=')
		i++;
	var_name = (char *) ft_calloc(i, sizeof(char));
	if (!var_name)
		err_free(0, data, 0, 0);
	i = 0;
	while (str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}

/*
** Depuis init_env, On the heap: line, data->env_lst
*/

char	*get_var_value(t_data *data, char *str)//CHECKED
{
	size_t	i;
	size_t	j;
	char	*var_value;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	var_value = (char *) ft_calloc(ft_strlen(str) - i, sizeof(char));
	if (!var_value)
		err_free(0, data, 0, 0);
	i++;
	while (str[i])
	{
		var_value[j] = str[i];
		i++;
		j++;
	}
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
			new = (t_env *) ft_calloc(1, sizeof(t_env));
			if (!new)
				err_free(0, data, 0, 0);
			env_add_front(&head, new);
			new->var = get_var_name(data, env[i]);
			new->value = get_var_value(data, env[i]);
			new->is_env = 1;
		}
		i++;
	}
	return (head);
}

/*
** Depuis add_var_value, On the heap: line, data->env_lst, output, var_name
*/

t_env	*find_var_env(t_data *data, char *var_name)//CHECKED
{
	t_env *temp;

	temp = data->env_lst;
	while(temp)
	{
		if (!ft_strcmp(var_name, temp->var))
			return (temp);
		temp = temp->next;
	}
	return(NULL);
}