/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:18:11 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/14 16:53:25 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_all_success(t_data *data)
{
	if (data->env_lst)
		ft_lstclear_env(data->env_lst);
	// faire une fonction qui full free la struct pipe
	// faire une fonction qui full free l-cmd
	if (data)
		free(data);
	exit(EXIT_SUCCESS);
}

void	free_all_failure(t_data *data)
{
	perror("Error : ");
	if (data->env_lst)
		ft_lstclear_env(data->env_lst);
	// faire une fonction qui full free la struct pipe
	// faire une fonction qui full free l-cmd
	if (data)
		free(data);
	exit(EXIT_FAILURE);
}

void	free_all(t_data *data, int n)
{
	if (data->env_lst)
		ft_lstclear_env(data->env_lst);
	// faire une fonction qui full free la struct pipe
	// faire une fonction qui full free l-cmd
	if (data)
		free(data);
	exit(n);
}


void	delete_one_env_list(t_env *lst)
{
	if (lst->var)
		free(lst->var);
	if (lst->value)
		free(lst->value);
	if (lst)
	{
		free(lst);
		lst = NULL;
	}
}

void	ft_lstclear_env(t_env *lst)
{
	t_env	*lst_next;
	t_env	*delete;

	if (lst)
	{
		lst_next = lst->next;
		while (lst_next)
		{
			delete = lst_next;
			lst_next = lst_next->next;
			delete_one_env_list(delete);
		}
		delete_one_env_list(lst);
	}
}
