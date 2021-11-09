/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:29:05 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/09 15:02:00 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_lstnew_cmd(char *raw)
{
	t_cmd	*list;

	list = malloc(sizeof(t_cmd *));
	if (!list)
		return (NULL);
	list->raw = raw;
	list->cmd_path = NULL;
	list->cmd = NULL;
	list->content = NULL;
	list->next = NULL;
	return (list);
}
