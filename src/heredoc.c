/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:31:43 by llalba            #+#    #+#             */
/*   Updated: 2021/12/06 15:45:46 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_bool	continue_reading(t_data *data, int *ret, char **save)
{
	char	buff[2];
	int		success;

	buff[1] = 0;
	buff[0] = getch(data);
	success = write(1, &buff, 1);
	if (!success)
		return (0);
	if (buff[0] == '\0')
		*ret = 0;
	else
		*ret = 1;
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
** It also writes "> " on stdout
*/

static int	get_next_line(t_data *data, char **line, t_bool flag)
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
	write(1, "> ", 2);
	if (!line)
		return (-1);
	ret = 1;
	while ((!save || !ft_strrchr(save, '\n')) && ret > 0)
	{
		if (!continue_reading(data, &ret, &save))
			return (-1);
	}
	return (gnl_result(ret, line, &save));
}

static void	heredoc_input(t_data *data, t_cmd *head, char *delimiter)
{
	char	*line;
	int		status;

	line = 0;
	head->heredoc = (char *)ft_calloc(1, sizeof(char));
	if (!(head->heredoc))
		err_free(MALLOC_ERROR, data, 0);
	status = get_next_line(data, &line, HEREDOC_CONT);
	while (status > 0 && ft_strcmp(delimiter, line) != 0)
	{
		ft_str_insert(&(head->heredoc), line, ft_strlen(head->heredoc));
		ft_str_insert(&(head->heredoc), "\n", ft_strlen(head->heredoc));
		free(line);
		line = 0;
		status = get_next_line(data, &line, HEREDOC_CONT);
	}
	(void)get_next_line(data, 0, HEREDOC_END);
	if (line)
		free(line);
	if (status == -1)
		err_free(GNL_ERROR, data, 0);
	else if (status == 0)
		write(2, HEREDOC_EOF, ft_strlen(HEREDOC_EOF));
}

static void	spot_heredoc(t_data *data, t_cmd *head)
{
	size_t	i;
	t_bool	sentinel;
	int		id;

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

void	load_heredoc(t_data *data)
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
