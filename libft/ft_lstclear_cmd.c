/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 11:52:06 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/07 12:05:02 by fmonbeig         ###   ########.fr       */
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

void	ft_lstclear_cmd(t_cmd *lst)
{
	t_cmd	*lst_next;
	t_cmd	*delete;

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
