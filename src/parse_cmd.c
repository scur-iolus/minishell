/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/15 18:47:27 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst, cmd_split, data->cmd->content
*/

static	fill_in_content(t_data *data, char **split, t_content *new, size_t *i)
{
	//short	was_left_chevron;
	//short	was_right_chevron;

	// incrémenter i autant que nécessaire
	//printf("head->raw : >>%s<<\n", head->raw); // FIXME ===================
	// MARQUE-PAGE															-
}

/*
** On the heap: line, data->env_lst
*/

static void	parse_cmd_content(t_data *data, t_cmd *head)
{
	size_t		i;
	t_content	*new;
	char		**cmd_split;

	cmd_split = ft_split(head->raw, ' ');
	if (!cmd_split)
		err_free(0, data, 0, 0);
	i = 0;
	while (cmd_split[i])
	{
		new = ft_lstnew_content();
		content_add_back(&(head->content), new);
		fill_in_content(data, cmd_split, new, &i);
	}
	ft_free_split(cmd_split);
}

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
		cmd_add_back(head, new);
		data->cmd = *head;
		i++;
	}
	data->cmd = *head;
}

/*
** On the heap: line, data->env_lst
** This func also checks that there isn't any | followed by spaces and another |
** In that case, an error is raised and the function returns
*/

void	parse_cmd_list(t_data *data)//CHECKED
{
	t_cmd	*head;

	head = 0;
	pipes_split_raw(data, &head);
	while (head)
	{
		if (ft_strchr(data->line, '|') && *(head->raw) == '\0')
		{
			ft_error(INVALID_CHAR_ERR);
			return ;
		}
		parse_cmd_content(data, head);
		head = head->next;

	}
}
