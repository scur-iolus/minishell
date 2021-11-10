/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:41:46 by llalba            #+#    #+#             */
/*   Updated: 2021/11/10 10:44:44 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	delete_one_env_var(t_env *lst)
{
	if (lst)
	{
		if (lst->var)
			free(lst->var);
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = NULL;
	}
}

void	ft_lstclear_env(t_env *head)
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
