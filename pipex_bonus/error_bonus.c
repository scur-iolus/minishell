/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:03:28 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/09/28 11:49:42 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	error_pipe(t_data *data)
{
	ft_putstr_fd("Error : Failed to open the pipe\n", 2);
	free_all_failure(data);
}

void	error_fork(t_data *data)
{
	ft_putstr_fd("Error : Failed to create the fork\n", 2);
	free_all_failure(data);
}

void	error_command(t_data *data)
{
	ft_putstr_fd("Error : command not found\n", 2);
	free_all_failure(data);
}

void	error_opening_file(t_data *data)
{
	ft_putstr_fd("Error : Failed to open the file\n", 2);
	free_all_failure(data);
}

void	error_not_enough_argument(t_data *data)
{
	ft_putstr_fd("Error : Wrong number of argument\n", 2);
	exit(EXIT_FAILURE);
}
