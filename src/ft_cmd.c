/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:31:57 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/15 18:02:33 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstsize(t_cmd *lst)//CHECKED
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

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
	new->content = NULL;
	new->next = NULL;
	return (new);
}