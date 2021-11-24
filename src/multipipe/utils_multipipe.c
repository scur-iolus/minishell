/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_multipipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:18:37 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/24 10:51:30 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	take_path(t_data *data)
{
	t_env	*tmp;

	tmp = find_var_env(data, "PATH");
	if (!tmp)
	{
		data->pipe->path = 0;
		return ;
	}
	data->pipe->path = ft_split(tmp->value, ':');
	if (!(data->pipe->path))
		err_free(MALLOC_ERROR, data, 0);
}

void	find_command_path(t_data *data, t_cmd *head)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->pipe->path && data->pipe->path[i])
	{
		tmp = ft_strjoin(data->pipe->path[i], "/");
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
	if (!head->cmd_path)
	{
		write(2, (head->cmd)[0], ft_strlen((head->cmd)[0]));
		write(2, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND));
	}
}
