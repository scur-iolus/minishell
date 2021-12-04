/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_multipipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:18:37 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/04 11:56:44 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	take_path(t_data *data)
{
	t_env	*tmp;

	tmp = find_var_env(data, "PATH");
	if (!tmp)
	{
		data->path = 0;
		return ;
	}
	data->path = ft_split(tmp->value, ':');
	if (!(data->path))
		err_free(MALLOC_ERROR, data, 0);
}

static char	*name_of_program(char *s1)
{
	char *ptr;

	s1 += 2;
	ptr = ft_strdup(s1);
	return (ptr);
}

static void	the_command_is_the_path(t_data *data, t_cmd *head)
{
	if (head->cmd[0][1] == '/')
	{
		head->cmd_path = name_of_program(head->cmd[0]);
		if (!head->cmd_path)
		{
			ft_error(MALLOC_ERROR);
			return;
		}
	}
	else
	{
		head->cmd_path = ft_strdup(head->cmd[0]);
		if (!head->cmd_path)
			ft_error(MALLOC_ERROR);
	}
}

void	find_command_path(t_data *data, t_cmd *head)
{
	int		i;
	char	*tmp;

	i = 0;
	if (head->cmd[0][0] == '/' || head->cmd[0][0] == '.')
	{
		the_command_is_the_path(data, head);
		return;
	}
	while (data->path && data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		if (!tmp)
			err_free(MALLOC_ERROR, data, 0);
		head->cmd_path = ft_strjoin(tmp, (head->cmd)[0]);
		free(tmp);
		if (!head->cmd_path)
			err_free(MALLOC_ERROR, data, 0);
		if (!access(head->cmd_path, X_OK))
			break ;
		free(head->cmd_path);
		head->cmd_path = 0;
		i++;
	}
}

void	command_failed(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
	write(2, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
	ft_putstr_fd(" : ", 2);
	err_free_command_not_found(CMD_NOT_FOUND, data, 0);
}
