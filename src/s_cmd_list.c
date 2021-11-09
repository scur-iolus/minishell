/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/09 17:00:56 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO : construire la liste chainee de s_cmd
// TODO : construire la liste chainee de s_info dans s_cmd


void	find_cmd_cmd(char *str, size_t *start, size_t *end)
{
	short	is_filename;

	is_filename = 0;
	(void)*start;
	(void)*end;
	// TODO ici ---------------------------------------------------------------
}

void	parse_cmd_cmd(t_cmd *head)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = start;
	find_cmd_cmd(head->raw, &start, &end);
}

static void	pipes_split_raw(t_cmd *head, char *line)
{
	char	**ptr;
	t_cmd	*new;
	size_t	i;

	i = 0;
	ptr = ft_split(line, '|');
	if (!ptr)
		exit(1); // TODO malloc error a gerer proprement
	while (ptr[i])
	{
		new = ft_lstnew_cmd(ft_strtrim(ptr[i], " 	"));
		ft_lstadd_back_cmd(&head, new);
		free(ptr[i]);
		i++;
	}
}

void	parse_cmd_list(t_data *data, char *line)
{
	t_cmd	*head;

	head = 0;
	pipes_split_raw(head, line);
	data->cmd = head;
	while (head)
	{
		parse_cmd_cmd(head);
		printf("head->raw : %s\n", head->raw); // FIXME =======================
		head = head->next;
	}
}
