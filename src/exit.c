/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:45:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/15 17:52:29 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_bool	check_nb_argument_ft_exit(char **cmd)
{
	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_error(TOO_MANY_ARG2);
			return (1);
		}
	}
	return (0);
}

static t_bool	check_argument_is_digit_ft_exit(char *str)
{
	int			i;
	long long	exit_status ;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	if (i > 10)
		return (1);
	exit_status = ft_atoi(str);
	if (exit_status < -2147483646 || exit_status > 2147483646)
		return (1);
	return (0);
}

void	ft_exit(t_data *data, char **cmd)
{
	long long	exit_status ;

	if (check_nb_argument_ft_exit(cmd))
		return ;
	if (cmd[1])
	{
		if (check_argument_is_digit_ft_exit(cmd[1]))
		{
			ft_error(NUMERIC_ARG);
			free_everything(data, 0);
			exit(2);
		}
		exit_status = ft_atoi(cmd[1]);
		free_everything(data, 0);
		exit((int)exit_status);
	}
	free_everything(data, 0);
	exit (0);
}
