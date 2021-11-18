/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:31:57 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/18 17:40:29 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_cmd	*ft_lstlast(t_cmd *lst)//CHECKED
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd **alst, t_cmd *new)//CHECKED
{
	t_cmd	*last;

	if (!(*alst))
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
	}
}

t_cmd	*ft_lstnew_cmd(char *raw)//CHECKED
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->raw = raw;
	new->cmd_path = NULL;
	new->cmd = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->heredoc = NULL;
	new->next = NULL;
	return (new);
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
		free(head);
		head = tmp;
	}
}
