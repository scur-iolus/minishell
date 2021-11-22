/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:31:43 by llalba            #+#    #+#             */
/*   Updated: 2021/11/22 22:25:59 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static short	continue_reading(int *ret, char **save)//CHECKED
{
	char	buff[BUFFER_SIZE + 1];

	*ret = read(0, buff, BUFFER_SIZE);
	if (*ret == -1)
		return (0);
	buff[*ret] = '\0';
	if (!(*save))
		*save = ft_strdup(buff);
	else
		ft_str_insert(save, buff, ft_strlen(*save));
	if (!(*save))
		return (0);
	return (1);
}

/*
** Customized GNL with free(line) when ret == 0, and a flag to free(save)
*/

static int	get_next_line(char **line, short flag)//CHECKED
{
	static char	*save = 0;
	int			ret;

	if (flag)
	{
		if (save)
			free(save);
		save = 0;
		return (42);
	}
	if (!line || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (-1);
	ret = 1;
	while (!contains_new_line(save) && ret > 0)
	{
		if (!continue_reading(&ret, &save))
			return (-1);
	}
	return (gnl_result(ret, line, &save));
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw
** and progressively data->cmd->split
*/

static void	heredoc_input(t_data *data, t_cmd *head, char *heredoc_delimiter)//CHECKED
{
	char	*line;
	int		status;

	line = 0;
	head->heredoc = (char *)ft_calloc(1, sizeof(char));
	if (!(head->heredoc))
		err_free(MALLOC_ERROR, data, 0);
	write(1, ">", 1);
	status = get_next_line(&line, HEREDOC_CONTINUE);
	while (status > 0 && ft_strcmp(heredoc_delimiter, line) != 0)
	{
		ft_str_insert(&(head->heredoc), line, ft_strlen(head->heredoc));
		ft_str_insert(&(head->heredoc), "\n", ft_strlen(head->heredoc));
		free(line);
		line = 0;
		write(1, ">", 1);
		status = get_next_line(&line, HEREDOC_CONTINUE);
	}
	(void)get_next_line(0, HEREDOC_END);
	if (line)
		free(line);
	if (status == -1)
		err_free(GNL_ERROR, data, 0);
	else if (status == 0)
		write(1, HEREDOC_EOF, ft_strlen(HEREDOC_EOF));
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw
** and progressively data->cmd->split
*/

static void	spot_heredoc(t_data *data, t_cmd *head)//CHECKED
{
	size_t	i;
	short	sentinel;

	i = 0;
	sentinel = 0;
	while ((head->split)[i])
	{
		if (sentinel && head->heredoc)
		{
			free(head->heredoc);
			head->heredoc = 0;
		}
		if (sentinel)
			heredoc_input(data, head, (head->split)[i]);
		if (!ft_strcmp("<<", (head->split)[i]))
			sentinel = 1;
		else
			sentinel = 0;
		i++;
	}
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw
** and progressively data->cmd->split
*/

void	load_heredoc(t_data *data)//CHECKED
{
	size_t	i;
	t_cmd	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		spot_heredoc(data, tmp);
		tmp = tmp->next;
	}
}
