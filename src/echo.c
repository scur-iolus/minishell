/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:59:53 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/02 20:37:05 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	echo_argument_n(char *str)
{
	int	i;

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

static void	print_echo_flag(char **cmd, int i)
{
	while (cmd[i] && cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
}

static void	print_echo(char **cmd, int i)
{
	while (cmd[i] && cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i] && !echo_argument_n(cmd[i]))  // si argument est bien un -n ou un -nnn alors i++ on passe les arguments
		i++;
	if (i > 1) // si -n on print sans le /n a la fin
		print_echo_flag(cmd, i);
	else
		print_echo(cmd, i);
	return (0);
}
