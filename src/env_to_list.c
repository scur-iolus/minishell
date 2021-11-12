/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:11:57 by llalba            #+#    #+#             */
/*   Updated: 2021/11/12 16:52:43 by llalba           ###   ########.fr       */
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
	while (str[i] != '=')
		i++;
	var_name = (char *) ft_calloc(i, sizeof(char));
	if (!var_name)
		err_free(MALLOC_ERROR, data, 0, 0);
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

char	*get_var_value(t_data *data, char *str)//FIXME ERROR A TROUVER ICI --------------------------------
{
	size_t	j;
	size_t	str_len;
	char	*var_value;

	j = 0;
	str_len = ft_strlen(str);
	while (*str && *str != '=')
		str++;
	if (*str == '=')
		var_value = (char *) ft_calloc(str_len - ft_strlen(str), sizeof(char));
	else
		var_value = (char *) ft_calloc(1, sizeof(char));
	if (!var_value)
		err_free(MALLOC_ERROR, data, 0, 0);
	if (*str)
		str++;
	while (*str)
	{
		var_value[j] = *str;
		str++;
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
		printf("✅%s\n", env[i]); //FIXME
		equals_sign = ft_strchr(env[i], '=');
		if (equals_sign)
		{
			new = ft_lstnew_env();
			if (!new)
				err_free(MALLOC_ERROR, data, 0, 0);
			env_add_front(&head, new);
			new->var = get_var_name(data, env[i]);
		//	new->value = get_var_value(data, env[i]);
			new->is_env = 1;
		//	printf("var : %s⏪\n", new->var); //FIXME
		//	printf("value : %s⏪\n", new->value); //FIXME
		//	printf("is_env : %d⏪\n", new->is_env); //FIXME
		//	fflush(stdout);//FIXME
		}
		i++;
	}
	return (head);
}
