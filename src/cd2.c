/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:33:11 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/03 14:54:33 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_directory(t_data *data) // FIXME petit souci de changement de PWD entre avec un cd home CDPATH="/"
{
	char	line[PATH_MAX];

	getcwd(line, PATH_MAX);
	switch_old_pwd(data, line);
	switch_pwd(data, line);
}

t_bool	arg_is_point_point(char *str)
{
	if (str[0] == '.')
		if(str[1] == '.')
			if(!str[2])
				return (1);
	if (str[0] == '.')
		if(!str[1])
			return (1);
	return (0);
}
