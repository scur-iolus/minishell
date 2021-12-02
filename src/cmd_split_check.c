/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/12/02 19:34:25 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst,
** and progressively data->cmd, data->cmd->raw
*/

static void	pipes_split(t_data *data, t_cmd **head)
{
	char	**ptr;
	t_cmd	*new;
	char	*trimmed;
	size_t	i;

	i = 0;
	ptr = ft_split(data->line, '|');
	if (!ptr)
		err_free(MALLOC_ERROR, data, 0);
	while (ptr[i])
	{
		trimmed = ft_strtrim(ptr[i], " 	");
		free(ptr[i]);
		if (!trimmed)
			err_free(MALLOC_ERROR, data, 0);
		new = ft_lstnew_cmd(trimmed);
		if (!new)
			err_free(MALLOC_ERROR, data, trimmed);
		cmd_add_back(head, new);
		data->cmd = *head;
		i++;
	}
	free(ptr);
	data->cmd = *head;
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw, data->cmd->split
*/

static t_bool	is_syntax_error(t_data *data)
{
	t_cmd	*tmp;
	char	*next;
	size_t	i;

	tmp = data->cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->split[i] && tmp->split[i + 1])
		{
			if ((ft_strchr(tmp->split[i], '>') && \
			ft_strchr(tmp->split[i + 1] + 1, '>')) \
			|| (ft_strchr(tmp->split[i], '>') && \
			ft_strchr(tmp->split[i + 1] + 1, '<')) \
			|| (ft_strchr(tmp->split[i], '<') && \
			ft_strchr(tmp->split[i + 1] + 1, '>')) \
			|| (ft_strchr(tmp->split[i], '<') && \
			ft_strchr(tmp->split[i + 1] + 1, '<')))
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw
** and progressively data->cmd->split
*/

static void	cmds_split(t_data *data)
{
	t_cmd	*tmp;
	char	*c;
	size_t	i;

	tmp = data->cmd;
	while (tmp)
	{
		replace_semicolon(tmp->raw, '|');
		secure_between_apo(tmp->raw, ' ');
		tmp->split = ft_split(tmp->raw, ' ');
		if (!(tmp->split))
			err_free(MALLOC_ERROR, data, 0);
		i = 0;
		while (tmp->split[i])
		{
			replace_semicolon(tmp->split[i], ' ');
			i++;
		}
		tmp = tmp->next;
	}
}

/*
** On the heap: line, data->env_lst
*/

t_bool	parse_cmd(t_data *data)
{
	t_cmd	*head;

	head = 0;
	secure_between_apo(data->line, '|');
	pipes_split(data, &head);
	cmds_split(data);
	
	if (is_syntax_error(data) == 1)
	{
		ft_error(INVALID_CHAR_ERR);
		return (0);
	}
	load_heredoc(data);
	head = data->cmd;
	while (head)
	{
		if (!parse_cmd_content(data, head))
			return (0);
		head = head->next;
	}
	return (1);
}
