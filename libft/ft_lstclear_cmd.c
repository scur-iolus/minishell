/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 11:52:06 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/06 15:55:06 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_split2(char **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i])
		free (ptr[i++]);
	free(ptr);
}

void	ft_lstclear_cmd(t_list *lst)
{
	t_list	*lst_next;
	t_list	*delete;

	if (lst)
	{
		lst_next = lst->next;
		while (lst_next)
		{
			delete = lst_next;
			lst_next = lst_next->next;
			if (delete->cmd_path)
				free(delete->cmd_path);
			if (delete->cmd)
				free_split2(delete->cmd);
			free (delete);
		}
		if (lst->cmd_path)
			free(lst->cmd_path);
		if (lst->cmd)
			free_split2(lst->cmd);
		free(lst);
	}
}
