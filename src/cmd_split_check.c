/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/19 17:07:51 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

short	open_file(t_cmd *head, char *file, short opening)//CHECKED
{
	int	fd;
	int	closed;

	if (opening == ONE_RIGHT)
		fd = open (file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (opening == TWO_RIGHT)
		fd = open (file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (opening == ONE_LEFT)
		fd = open (file, O_RDONLY);
	if (fd == -1)
		return (0);
	closed = 0;
	if (head->infile && opening == ONE_LEFT)
		closed = close(head->infile);
	else if (head->outfile && \
	(opening == ONE_RIGHT || opening == TWO_RIGHT))
		closed = close(head->outfile);
	if (closed == -1)
		return (0);
	return (1);
}

/*
** On the heap: line, data->env_lst,
** and progressively data->cmd, data->cmd->raw
*/

static void	pipes_split(t_data *data, t_cmd **head)//CHECKED
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
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw
*/

static short	is_syntax_error(t_data *data)//CHECKED
{
	t_cmd	*tmp;
	int		s;

	s = 0;
	tmp = data->cmd;
	while (tmp)
	{
		if (s != 1 && ((ft_strchr(data->line, '|') && *(tmp->raw) == '\0') \
			|| (ft_strchr(tmp->raw, '>') && ft_strchr(tmp->next->raw, '>'))\
			|| (ft_strchr(tmp->raw, '>') && ft_strchr(tmp->next->raw, '<'))\
			|| (ft_strchr(tmp->raw, '<') && ft_strchr(tmp->next->raw, '>'))\
			|| (ft_strchr(tmp->raw, '<') && ft_strchr(tmp->next->raw, '<'))\
			))
			s = 1;
		tmp = tmp->next;
	}
	return s;
}

/*
** On the heap: line, data->env_lst
*/

short	parse_cmd(t_data *data)
{
	t_cmd			*head;

	head = 0;
	pipes_split(data, &head);
	if (is_syntax_error(data) == 1)
	{
		ft_error(INVALID_CHAR_ERR);
		return ;
	}
	load_heredoc(data);
	head = data->cmd;
	while (head)
	{
		//if (!parse_cmd_content(data, head))
		//	return (0);
		head = head->next;
		printf("\n");//FIXME
	}
	return (1);
}
