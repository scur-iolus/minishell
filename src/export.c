/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:36:27 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/12 17:58:28 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export(t_data *data, char *line) // changer avec la line du parsing // faut il afficher la liste en ordre alphabetique ??
// l idee c est de chercher la chaine de char apres la commande
{
	t_env *new;

	if (line)
	{
		new = (t_env *) malloc(sizeof(t_env));
		new->var = get_var_name(line);
		new->value = get_var_value(line); // s accorder sur le parsing
		new->is_env = check_is_env(line);
		env_add_front(data->env_lst, new);
	}
	else
	{
		//afficher tout l env + export avec les flags
	}
}

int	check_is_env(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '=')
			return (1);
	}
	return (0);
}
