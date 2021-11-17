/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/17 17:35:03 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

short	file_can_be_opened(char *file)//CHECKED
{
	int	fd;
	int	success;

	fd = open (file, O_RDONLY | O_CREAT);
	if (fd == -1)
		return (0);
	success = close(fd);
	if (success == -1)
		return (0);
	return (1);
}

/*
** On the heap: line, data->env_lst, and progressively data->cmd
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
	free(ptr);
	data->cmd = *head;
}

/*
** On the heap: line, data->env_lst, data->cmd
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
	pipes_split_raw(data, &head);
	if (is_syntax_error(data) == 1)
	{
		ft_error(INVALID_CHAR_ERR);
		return ;
	}
	head = data->cmd;
	while (head)
	{
		if (!parse_cmd_content(data, head))
			return (0);
		head = head->next;
		printf("\n");//FIXME
	}
	return (1);
}
