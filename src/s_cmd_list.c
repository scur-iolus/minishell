/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/09 11:35:22 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_cmd_cmd(t_cmd *head)
{
	while (head)
	{
		head->cmd = ft_split(head->content, ' ');
		head = head->next;
	}
}

// TODO : construire la liste chainee de s_cmd
// TODO : construire la liste chainee de s_info dans s_cmd

// TODO checker que head->next = 0 dans la boucle ci-dessous
// TODO proteger les split

void	parse_cmd_list(t_data *data, char *line)
{
	char	**ptr;
	char	*tmp;
	size_t	i;

	i = 0;
	ptr = ft_split(line, '|');
	while (ptr[i])
	{
		tmp = ptr[i];
		ptr[i] = ft_strtrim(ptr[i], ' 	');
		free(tmp);
		i++;
	}

}