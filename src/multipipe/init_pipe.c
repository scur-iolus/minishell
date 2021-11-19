/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:18:10 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/19 18:45:44 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_pipe(int nb_pipe, t_data *data)
{
	int	i;

	i = -1;
	data->pipe->end = ft_calloc(nb_pipe, sizeof(int *));
	if (!data->pipe->end)
	{
		ft_putstr_fd("ERROR: Malloc Failed", 2);
		return ;   //FIXME : est ce qu on doit tout fermer ??
	}
	while (++i < nb_pipe)
	{
		data->end[i] = ft_calloc(2, sizeof(int));
		if (!data->end[i])
		{
		ft_putstr_fd("ERROR: Malloc Failed", 2);
		return ;   //FIXME : est ce qu on doit tout fermer ??
		}
		pipe(data->end[i]);
		if (pipe(data->end[i]) == -1)
		{
		ft_putstr_fd("ERROR: Malloc Failed", 2);
		return ;   //FIXME : est ce qu on doit tout fermer ??
		}
	}
}

void	init_pipe_struct(t_pipe *pipe, t_data *data)
{
	pipe->end = NULL;
	pipe-> nb_pipe = ft_lstsize(data->cmd) + 1;
	init_pipe(pipe->nb_pipe, data);//pipe initialisé en fonction de la longueur de la liste chainées commande // X process + 1
}

void	multi_pipe(t_data *data)
{
	t_pipe pipe;

	init_pipe_struct(&pipe, data);
	pipex(pipe.arg, data, data->env);
}

//NOTA BENE si on a qu une commande faire un do one cmd, si on en a plusieurs il faut verifier les redirections, pour chaque commande si ouverture de fichier alors on ecrase le end[0] par le dup2 du fichier
//			faire une fonction qui va gerer correctements l ouverture des dup et une autre pour leurs fermetures

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
