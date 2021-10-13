/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:11:57 by llalba            #+#    #+#             */
/*   Updated: 2021/10/12 17:45:31 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_add_front(t_env **head, t_env *new)
{
	t_env	*temp;

	temp = *head;
	*head = new;
	new->next = temp;
}

char	*get_var_name(char *str)
{
	size_t	i;
	char	*var_name;

	i = 0;
	while (str[i] != '=')
		i++;
	var_name = (char *) ft_calloc(i, sizeof(char));
	if (!var_name)
		exit (1); // malloc fail, free et exit à coder proprement
	i = 0;
	while (str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}

char	*get_var_value(char *str)
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
		exit (1); // malloc fail, free et exit à coder proprement
	i++;
	while (str[i])
	{
		var_value[j] = str[i];
		i++;
		j++;
	}
	return (var_value);
}

t_env	*init_env(char **env)
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
		if (!equals_sign)
			exit (1); // erreur à gérer, pas de signe égal dans env[i], c'est pas censé arriver
		new = (t_env *) malloc(sizeof(t_env));
		new->var = get_var_name(env[i]);
		new->value = get_var_value(env[i]);
		new->is_env = 1;
		env_add_front(&head, new);
		i++;
	}
	return (head);
}

t_env	*find_var_env(t_data *data, char *var_name)
{
	t_env *temp;
	int i;

	temp = data->env_lst;
	i = -1;
	while(temp)
	{
		if (!ft_strcmp(var_name, temp->var))
			return (temp);
		temp = temp->next;
	}
	return(NULL);
}
