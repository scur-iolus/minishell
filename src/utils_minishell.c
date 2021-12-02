/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:33:03 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/02 17:34:29 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_var_shlvl(t_data *data)
{
	t_env *temp;
	int	i;

	temp = find_var_env(data, "SHLVL");
	if (temp)
	{
		i = ft_atoi(temp->value);
		i++;
		free(temp->value);
		temp->value = ft_itoa(i);
		if (!temp->value)
			ft_error(MALLOC_ERROR);
	}
}
