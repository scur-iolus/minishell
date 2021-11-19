/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:31:43 by llalba            #+#    #+#             */
/*   Updated: 2021/11/19 17:48:20 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_next_line(char **line, short done)
{
	static char	*remainder = 0;

	if (done && remainder)
	{
		free(remainder);
		remainder = 0;
		//MARQUE-PAGE https://github.com/fmonbeig/42-school/blob/master/pipex/pipex_bonus/get_next_line/get_next_line.c
	}
	if (!remainder)
		remainder = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));

	return (0);
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw
** and progressively data->cmd->split
*/

static void	heredoc_input(t_data *data, t_cmd *head, char *str)
{
	char	*line;
	int		status;

	line = 0;
	head->heredoc = (char *)ft_calloc(1, sizeof(char));
	if (head->heredoc)
		err_free(MALLOC_ERROR, data, 0);
	status = get_next_line(&line, HEREDOC_NOT_FOUND);
	while (status > 0 && ft_strcmp(str, line) != 0)
	{
		ft_str_insert(&(head->heredoc), line, ft_strlen(head->heredoc));
		ft_str_insert(&(head->heredoc), "\n", ft_strlen(head->heredoc));
		write(1, ">", 1);
		status = get_next_line(&line, HEREDOC_NOT_FOUND);
	}
	if (line)
		free(line);
	if (status == -1)
		err_free(GNL_ERROR, data, 0);
	if (ft_strcmp(str, line) == 0)
		(void)get_next_line(0, HEREDOC_FOUND);
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw
** and progressively data->cmd->split
*/

static void	spot_heredoc(t_data *data, t_cmd *head)
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
		if (ft_strcmp("<<", (head->split)[i]))
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

void	load_heredoc(t_data *data)
{
	size_t	i;
	t_cmd	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		tmp->split = ft_split(tmp->raw, ' ');
		if (!(tmp->split))
			err_free(MALLOC_ERROR, data, 0);
		spot_heredoc(data, tmp);
		tmp = tmp->next;
	}
}
