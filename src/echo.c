/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:59:53 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/15 16:50:42 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_data *data, char *line) // envoyer la commande pour savoir s'il y a le flag
{

	data->exit_status = 0;
	//fonction qui trime le debut et la fin de la line au niveau des non espace + non printable voir Fonction de Louis
	ft_putstr_fd(line, 1); // en vrai il faut echo le nombre de nom de cmd (voir parsing)

	//if il y a un pipe et qu il n y a aucune info dans le pipe alors error.

	if (ft_strcmp("-n", line)) // normalement il y a -n dans le parsing
	ft_putstr_fd(line, 1);
}
