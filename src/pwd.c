/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/06 16:20:07 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_data *data, char **cmd)
{
	char	*line;

	line = NULL;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			ft_error(INVALID_OPTION);
			return (1);
		}
	}
	line = getcwd(line, PATH_MAX);
	if (!line)
	{
		free (line);
		ft_error("error retrieving current directory\n");
		return (1);
	}
	free (line);
	ft_putstr_fd(line, 1);
	write(1, "\n", 1);
	return (0);
}
