/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/08 16:11:05 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	build_cmd_list(t_data *data, char *line)
{
	char	**ptr;
	t_cmd	*head;
	size_t	i;

	i = 0;
	head = 0;
	ptr = ft_split(line, '|');
	while (ptr[i])
	{
		ft_lstadd_back_cmd(&head, ft_lstnew_cmd(ft_strtrim(ptr[i], ' 	')));
		free(ptr[i]);
		i++;
	}


}