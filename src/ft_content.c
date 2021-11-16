/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_content.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:36:16 by llalba            #+#    #+#             */
/*   Updated: 2021/11/16 14:08:45 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_content	*ft_lstnew_content(void)//CHECKED
{
	t_content	*new;

	new = (t_content *) malloc(sizeof(t_content));
	if (!new)
		return (0);
	new->str = 0;
	new->in = 0;
	new->out = 0;
	new->pos = 0;
	new->next = 0;
	return (new);
}

static t_content	*ft_lstlast(t_content *lst)//CHECKED
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	content_add_back(t_content **alst, t_content *new)//CHECKED
{
	t_content	*last;

	if (!(*alst))
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
	}
}

void	content_add_front(t_content **head, t_content *new)//CHECKED
{
	t_content	*temp;

	temp = *head;
	*head = new;
	new->next = temp;
}

/*
** On the heap: line, data->env_lst, cmd_split, data->cmd->contentS
*/

short	add_str_content(t_cmd *head, char *str_content)
{
	return (1);
}
