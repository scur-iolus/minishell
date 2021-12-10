/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:31:43 by llalba            #+#    #+#             */
/*   Updated: 2021/12/10 18:41:43 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	heredoc_input(t_data *data, t_cmd *head, char *delimiter)
{
	char	*line;
	int		status;

	line = 0;
	head->heredoc = (char *)ft_calloc(1, sizeof(char));
	if (!(head->heredoc))
		err_free(MALLOC_ERROR, data, 0);
	write(1, "> ", 2);
	status = get_next_line(&line, HEREDOC_CONT);
	while (status > 0 && ft_strcmp(delimiter, line) != 0)
	{
		ft_str_insert(&(head->heredoc), line, ft_strlen(head->heredoc));
		ft_str_insert(&(head->heredoc), "\n", ft_strlen(head->heredoc));
		free(line);
		line = 0;
		write(1, "> ", 2);
		status = get_next_line(&line, HEREDOC_CONT);
	}
	(void)get_next_line(0, HEREDOC_END);
	if (line)
		free(line);
	if (status == -1)
		err_free(GNL_ERROR, data, 0);
	else if (status == 0)
		write(2, HEREDOC_EOF, ft_strlen(HEREDOC_EOF));
}

static void	write_to_pipe(t_data *data, t_cmd *head, int fd[2], char *delimiter)
{
	int		ret;
	char	*c;

	free_everything(data, 0);
	signals_init_child();
	data->new_status = IS_HEREDOC;
	heredoc_input(data, head, delimiter);
	ret = close(fd[0]);
	if (ret == -1)
		err_free(CLOSE_FAILED, data, 0);
	c = head->heredoc;
	while (c && *c)
	{
		write(fd[1], c, 1);
		c++;
	}
	write(fd[1], "\0", 1);
	ret = close(fd[1]);
	if (ret == -1)
		err_free(CLOSE_FAILED, data, 0);
	exit(data->new_status);
}

static void	read_from_pipe(t_data *data, t_cmd *head, int fd[2])
{
	int		ret;
	char	c[2];

	data->new_status = HAS_HEREDOC;
	ret = close(fd[1]);
	if (ret == -1)
		err_free(CLOSE_FAILED, data, 0);
	head->heredoc = (char *)ft_calloc(1, sizeof(char));
	if (!(head->heredoc))
		err_free(MALLOC_ERROR, data, 0);
	c[0] = 1;
	c[1] = '\0';
	ret = 1;
	while (ret && c[0] != '\0')
	{
		ret = read(fd[0], &(c[0]), 1);
		if (c[0])
			ft_str_insert(&(head->heredoc), &(c[0]), ft_strlen(head->heredoc));
	}
	ret = close(fd[0]);
	if (ret == -1)
		err_free(CLOSE_FAILED, data, 0);
}

static t_bool	fork_heredoc(t_data *data, t_cmd *head, char *str)
{
	int		ret;
	int		status;
	int		fd[2];
	char	delimiter[DELIMITER_LEN + 1];

	if (pipe(fd) == -1)
		err_free(PIPE_FAILED, data, 0);
	ret = fork();
	if (ret == -1)
		err_free(FORK_FAILED, data, 0);
	if (ret == 0)
	{
		if (!load_delimiter(&(delimiter[0]), str))
			return (0);
		write_to_pipe(data, head, fd, delimiter);
	}
	else
	{
		read_from_pipe(data, head, fd);
		ret = wait(&status);
		update_status(status);
	}
	return (1);
}

t_bool	load_heredoc(t_data *data)
{
	size_t	i;
	t_bool	sentinel;
	t_cmd	*head;

	head = data->cmd;
	while (head && *g_status != 130)
	{
		i = -1;
		sentinel = 0;
		while ((head->split)[++i] && *g_status != 130)
		{
			if (sentinel && head->heredoc)
			{
				free(head->heredoc);
				head->heredoc = 0;
			}
			if (sentinel && !fork_heredoc(data, head, (head->split)[i]))
				return (0);
			sentinel = 0;
			if (!ft_strcmp("<<", (head->split)[i]))
				sentinel = 1;
		}
		head = head->next;
	}
	return (1);
}
