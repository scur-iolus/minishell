/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:53:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/07 12:20:17 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	multi_pipe(t_data *data, char **env) // pipex en cours de reconstruction 
{

		data = init_struct_pipe(argc, argv, &data); // changer l initialisation de structure
		take_env(data, env); // on prend les différents PATH dans l'environnement --> on garde
		parse_cmd(argc, argv, data); // étape devant être fait avant lors du parsing
		init_pipe(argc, data); //pipe initialisé en fonction de la longueur de la liste chainées commande 
		pipex(argc, data, env);
		free_all_success(data);
}