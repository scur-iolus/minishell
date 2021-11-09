/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/09 11:38:29 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	multi_pipe(t_data *data) // pipex en cours de reconstruction
{
	t_pipe pipe;

	data->pipe = init_struct_pipe(&pipe); // OK
	take_path(data); // OK
	init_pipe(argc, data); //pipe initialisé en fonction de la longueur de la liste chainées commande
	pipex(argc, data, env);
	free_all_success(data);
}
