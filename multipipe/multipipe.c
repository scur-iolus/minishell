/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/07 18:21:53 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	multi_pipe(t_data *data) // pipex en cours de reconstruction
{
	t_pipe pipe;

	data->pipe = init_struct_pipe(&pipe); // OK
	take_env(data); // on prend les différents PATH dans l'environnement --> A REFAIRE

	parse_cmd(argc, argv, data); // étape devant être fait avant lors du parsing
	init_pipe(argc, data); //pipe initialisé en fonction de la longueur de la liste chainées commande
	pipex(argc, data, env);
	ree_all_success(data);
}
