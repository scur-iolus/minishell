/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/12/10 18:44:48 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static t_bool	is_syntax_error_1(t_cmd *tmp)
{
	size_t	i;
	char	**split;

	while (tmp)
	{
		i = 0;
		while (tmp->split[i] && tmp->split[i + 1])
		{
			split = tmp->split;
			if ((!ft_strcmp(">", split[i]) && !ft_strcmp(">>", split[i + 1])) \
			|| (!ft_strcmp(">", split[i]) && !ft_strcmp(">", split[i + 1])) \
			|| (!ft_strcmp("<", split[i]) && !ft_strcmp(">>", split[i + 1])) \
			|| (!ft_strcmp("<", split[i]) && !ft_strcmp(">", split[i + 1])) \
			|| (!ft_strcmp(">>", split[i]) && !ft_strcmp(">>", split[i + 1])) \
			|| (!ft_strcmp(">>", split[i]) && !ft_strcmp(">", split[i + 1])) \
			|| (!ft_strcmp("<<", split[i]) && !ft_strcmp(">>", split[i + 1])) \
			|| (!ft_strcmp("<<", split[i]) && !ft_strcmp(">", split[i + 1])))
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

static t_bool	is_syntax_error_2(t_cmd *tmp)
{
	size_t	i;
	char	**split;

	while (tmp)
	{
		i = 0;
		while (tmp->split[i] && tmp->split[i + 1])
		{
			split = tmp->split;
			if ((!ft_strcmp(">", split[i]) && !ft_strcmp("<<", split[i + 1])) \
			|| (!ft_strcmp(">", split[i]) && !ft_strcmp("<", split[i + 1])) \
			|| (!ft_strcmp("<", split[i]) && !ft_strcmp("<<", split[i + 1])) \
			|| (!ft_strcmp("<", split[i]) && !ft_strcmp("<", split[i + 1])) \
			|| (!ft_strcmp(">>", split[i]) && !ft_strcmp("<<", split[i + 1])) \
			|| (!ft_strcmp(">>", split[i]) && !ft_strcmp("<", split[i + 1])) \
			|| (!ft_strcmp("<<", split[i]) && !ft_strcmp("<<", split[i + 1])) \
			|| (!ft_strcmp("<<", split[i]) && !ft_strcmp("<", split[i + 1])))
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	cmds_split(t_data *data)
{
	t_cmd	*tmp;
	char	*c;
	size_t	i;

	tmp = data->cmd;
	while (tmp)
	{
		secure_between(tmp->raw, '|', ';', TRUE);
		secure_between(tmp->raw, ' ', ';', FALSE);
		tmp->split = ft_split(tmp->raw, ' ');
		if (!(tmp->split))
			err_free(MALLOC_ERROR, data, 0);
		i = 0;
		while (tmp->split[i])
		{
			secure_between(tmp->split[i], ' ', ';', TRUE);
			if (!remove_surrounding_quotes((tmp->split) + i))
				err_free(MALLOC_ERROR, data, 0);
			i++;
		}
		tmp = tmp->next;
	}
}

t_bool	parse_cmd(t_data *data)
{
	t_cmd	*head;

	head = 0;
	secure_between(data->line, '|', ';', FALSE);
	pipes_split(data, &head);
	cmds_split(data);
	if (is_syntax_error_1(data->cmd) == 1 || is_syntax_error_2(data->cmd) == 1)
	{
		ft_error(INVALID_CHAR);
		return (0);
	}
	if (!load_heredoc(data))
		return (0);
	if (data->new_status == 143)
		data->new_status = 0;
	head = data->cmd;
	while (head)
	{
		if (!parse_cmd_content(data, head))
			return (0);
		head = head->next;
	}
	return (1);
}
