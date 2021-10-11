/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:11:57 by llalba            #+#    #+#             */
/*   Updated: 2021/10/11 16:39:44 by llalba           ###   ########.fr       */
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

char	*get_var_name(char *str, char *equals_sign)
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

char	*get_var_value(char *str, char *equals_sign)
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
		new->var = get_var_name(env[i], equals_sign);
		new->value = get_var_value(env[i], equals_sign);
		env_add_front(&head, new);
		i++;
	}
	return (head);
}
