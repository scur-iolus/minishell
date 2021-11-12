/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/12 15:33:56 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO : construire la liste chainee de s_cmd
// TODO : construire la liste chainee de s_info dans s_cmd


//void	find_cmd_cmd(char *str, size_t *start, size_t *end)
//{
//	short	is_filename;
//
//	is_filename = 0;
//	(void)*start;
//	(void)*end;
//	// TODO ici ---------------------------------------------------------------
//}
//
//void	parse_cmd_cmd(t_data *data, t_cmd *head)
//{
//	size_t	start;
//	size_t	end;
//
//	start = 0;
//	end = start;
//	find_cmd_cmd(head->raw, &start, &end);
//}

/*
** On the heap: line, data->env_lst and the linked list starting at *head
*/

static void	pipes_split_raw(t_data *data, t_cmd **head)//CHECKED
{
	char	**ptr;
	t_cmd	*new;
	char	*trimmed;
	size_t	i;

	i = 0;
	ptr = ft_split(data->line, '|');
	if (!ptr)
		err_free(MALLOC_ERROR, data, 0, 0);
	while (ptr[i])
	{
		trimmed = ft_strtrim(ptr[i], " 	");
		free(ptr[i]);
		if (!trimmed)
			err_free(MALLOC_ERROR, data, 0, 0);
		new = ft_lstnew_cmd(trimmed);
		if (!new)
			err_free(MALLOC_ERROR, data, trimmed, 0);
		ft_lstadd_back_cmd(head, new);
		i++;
	}
}

/*
** On the heap: line, data->env_lst
*/

void	parse_cmd_list(t_data *data)
{
	t_cmd	*head;

	head = 0;
	pipes_split_raw(data, &head);
	data->cmd = head;
	while (head)
	{
		//parse_cmd_cmd(data, head);
		printf("head->raw : >>%s<<\n", head->raw); // FIXME =======================
		head = head->next;
	}
}
