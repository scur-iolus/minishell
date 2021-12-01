/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:45:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/25 17:45:58 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_data *data, char *str, char **split, long long exit_status)
{
	if (exit_status < -2147483646 || exit_status > 2147483646)
	{
		ft_error(INVALID_STATUS);
		return ;
	}
	// FIXME  --> le exit status doit etre par exemple 99 dans la cmd exit 99
	//FIXME il faut atoi CMD[1]
	ft_putstr_fd("exit\n", 1);
	if (split)
		ft_free_split(split);
	free_everything(data, str);
	exit((int)exit_status);
}

static short	check_nb_argument_ft_exit(char **cmd)
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

static short	check_argument_is_digit_ft_exit(char *str)
{
	int i;
	long long int exit_status ;

	i = -1;
	while(str[++i])
	{
		if (!ft_isdigit(str[i]))
			return(1);
	}
	if (i > 10)
		return (1);
	exit_status = ft_atoi(str);
	if (exit_status < -2147483646 || exit_status > 2147483646)
		return (1);
	return (0);
}

void	ft_exit2(t_data *data, char **cmd)
{
	long long int exit_status ;

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
		exit_status = ft_atoi(cmd[1]); // NOTA BENE j ai change le atoi pour qu il corresponde a un int
		free_everything(data, 0);
		exit((int)exit_status);
	}
	free_everything(data, 0);
	exit(1); // si exit sans exit status
}
