/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:31:57 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/30 12:21:25 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** From add_var_value, on the heap: line, data->env_lst, output, var_name
*/

t_env	*find_var_env(t_data *data, char *var_name)//CHECKED
{
	t_env *temp;

	temp = data->env_lst;
	while (temp)
	{
		if (!ft_strcmp(var_name, temp->var))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	env_add_front(t_env **head, t_env *new)//CHECKED
{
	t_env	*temp;

	temp = *head;
	*head = new;
	new->next = temp;
}

t_env	*ft_lstnew_env(void)//CHECKED
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->is_env = 0;
	new->var = 0;
	new->value = 0;
	new->next = 0;
	return (new);
}

void	delete_one_env_var(t_env *lst)//CHECKED
{
	if (lst)
	{
		if (lst->var)
			free(lst->var);
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = 0;
	}
}

void	ft_lstclear_env(t_env *head)//CHECKED
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		tmp = head->next;
		delete_one_env_var(head);
		head = tmp;
	}
}
