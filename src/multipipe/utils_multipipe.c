/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_multipipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:18:37 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/18 19:02:21 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	take_path(t_data *data)
{
	t_env *temp;

	temp = find_var_env(data, "PATH"); // si temp->value est egale a zero qu est ce qu il se passe ??
										// est ce qu on doit le protect ?
	data->path = ft_split(temp->value, ':');
}

void	parse_cmd(t_data *data, char *cmd_line) // ici la fonction va créer la nouvelle liste cmd en remplissant cmd et cmd_path
{
	//cmd_line = string de la commande avec ses arguments. ex : cat -e  ou head -1
	int		i;
	t_cmd	*new;

	new->cmd = ft_split(cmd_line, ' ');
	if (!new->cmd)
		free_all(data, 1);
	find_command_path(data, new, cmd_line);
	ft_lstadd_back(data->cmd, new);
}

void	find_command_path(t_data *data, t_cmd *new, char *cmd_line) // Comment on passe les infos ici et comment on crée la liste chaînées
{
	int		i;
	int		h;
	char	*tmp;

	i = -1;
	while (data->path[++i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		new->cmd_path = ft_strjoin(tmp, new->cmd[0]);
		free(tmp);
		h = access(new->cmd_path, F_OK);
		if (!h)
			break ;
		else
		{
			free(new->cmd_path);
			new->cmd_path = NULL;
		}
	}
}
