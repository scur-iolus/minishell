/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:40:49 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/06 17:35:12 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	multi_pipe(int argc, char **argv, char **env) // pipex en cours de reconstruction 
{
	int		fd1;
	int		fd2;
	t_data	data;

	if (argc >= 5)
	{
		data = init_struct(argc, argv, &data); // changer l initialisation de structure
		take_env(data, env); // on prend les différents PATH dans l'environnement --> on garde
		parse_cmd(argc, argv, data); // étape devant être fait avant lors du parsing
		init_pipe(argc, data); //pipe initialisé en fonction de la longueur de la liste chainées commande 
		pipex(argc, data, env);
		free_all_success(data);
	}
	else
		error_not_enough_argument(data);
}

void	pipex(int argc, t_data *data, char **env)
{
	int	cmd_numb;
	int	pid;
	int	x;

	cmd_numb = 0;
	x = -1;
	while (++x < argc - 3 - data->flag_hd)
	{
		++cmd_numb;
		data->i++;
		pid = fork();
		if (pid < 0)
			error_fork(data);
		if (pid == 0)
			do_cmd(cmd_numb, argc, data, env);
	}
	parent_process(data, argc, pid);
}

void	do_cmd(int cmd_numb, int argc, t_data *data, char **env)
{
	if (cmd_numb == 1)
		first_process(data, argc, select_list(cmd_numb, data), env);
	else if (cmd_numb > 1 && cmd_numb < argc - 3 - data->flag_hd)
		middle_process(data, argc, select_list(cmd_numb, data), env);
	else if (cmd_numb == argc - 3 - data->flag_hd)
		last_process(data, argc, select_list(cmd_numb, data), env);
}
