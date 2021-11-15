/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:41:36 by llalba            #+#    #+#             */
/*   Updated: 2021/11/15 17:36:00 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_lstclear_content(t_content *head)//CHECKED
{
	t_content	*tmp;

	tmp = head;
	while (tmp)
	{
		tmp = head->next;
		if (head->str)
			free(head->str);
		free(head);
		head = tmp;
	}
}

void	ft_lstclear_cmd(t_cmd *head)//CHECKED
{
	t_cmd	*tmp;

	tmp = head;
	while (tmp)
	{
		tmp = head->next;
		if (head->raw)
			free(head->raw);
		if (head->cmd)
			ft_free_split(head->cmd);
		if (head->cmd_path)
			free(head->cmd_path);
		if (head->content)
			ft_lstclear_content(head->content);
		free(head);
		head = tmp;
	}
}