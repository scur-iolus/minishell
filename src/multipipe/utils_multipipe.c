/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_multipipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:18:37 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/11 18:57:27 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	take_path(t_data *data)
{
	t_env *temp;

	temp = find_var_env(data, "PATH"); // si temp->value est equale a zero qu est ce qu il se passe ??
										// est ce qu on doit le protect ?
	data->pipe->path = ft_split(temp->value, ':');
}

void	parse_cmd(t_data *data, char *cmd_line) // split une commande afin d'avoir chaque argument dans une string + trouve le Path de la commande
{
	//cmd_line = string de la commande avec ses arguments. ex : cat -e
	int		i;
	t_cmd	*new;

	data->l_cmd->cmd = ft_split(cmd_line, ' ');
	if (!data->l_cmd->cmd)
		exit(1); // mettre la fonction qui free
	find_command_path(data, );
}

void	find_command_path(t_data *data, char *cmd_line) // Comment on passe les infos ici et comment on crée la liste chaînées
{
	int		i;
	int		h;
	char	*tmp;

	i = -1;
	while (data->path[++i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		list->cmd_path = ft_strjoin(tmp, data->cmd[0]);
		free(tmp);
		h = access(list->cmd_path, F_OK);
		if (!h)
			break ;
		else
		{
			free(list->cmd_path);
			list->cmd_path = NULL;
		}
	}
}
