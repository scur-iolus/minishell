/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:59:53 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/16 17:33:41 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	ft_echo(t_data *data, char **cmd)
{
	int i;

	i = 1;
	data->exit_status = 0;
	while (!echo_argument_n(cmd[i]))  // si argument est bien un -n ou un -nnn alors i++ on passe les arguments
		i++;
	if (i > 1) // si -n on print sans le /n a la fin
	{
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			ft_putstr_fd(" ", 1);
			i++;
		}
		ft_putstr_fd("\n", 1);
	}
	else
	{
		while (cmd[++i])
		{
			ft_putstr_fd(cmd[i], 1);
			ft_putstr_fd(" ", 1);
		}
	}
}

int		echo_argument_n(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (1);
	if (str[i] == 'n')
		i++;
	else
		return (1);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}
