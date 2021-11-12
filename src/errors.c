/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:14:54 by llalba            #+#    #+#             */
/*   Updated: 2021/11/12 11:19:53 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Basically prints an error message on fd 2
*/

void	ft_error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

/*
** err_free properly frees all memory that has been allocated with malloc
** and exits the program with exit_status 1.
*/

void	err_free(char *msg, t_data *data, char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	free_data(data);
	if (msg && *msg)
		ft_error(msg);
	else
		ft_error(MALLOC_ERROR);
	exit(EXIT_FAILURE);
}
