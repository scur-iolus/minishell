/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:29:05 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/06 15:26:16 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_cmd(char **cmd)
{
	t_list	*list;

	list = malloc(sizeof(*list));
	list->cmd_path = NULL;
	if (!list)
		return (NULL);
	list->cmd = cmd;
	list->next = NULL;
	return (list);
}
