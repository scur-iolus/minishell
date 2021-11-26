/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_multipipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:18:37 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/26 12:03:19 by fmonbeig         ###   ########.fr       */
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

void	find_command_path(t_data *data, t_cmd *head)
{
	int		i;
	char	*tmp;

	i = 0;
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
