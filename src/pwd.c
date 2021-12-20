/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:01:58 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/20 15:53:37 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_data *data, char **cmd)
{
	char	line[PATH_MAX];
	int		j;
	char	*ret;

	j = -1;
	while (++j < PATH_MAX)
		line[j] = 0;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			ft_error(INVALID_OPTION);
			return (1);
		}
	}
	ret = getcwd(line, PATH_MAX);
	if (!ret)
	{
		ft_error("error retrieving current directory\n");
		return (1);
	}
	ft_putstr_fd(line, 1);
	write(1, "\n", 1);
	return (0);
}
