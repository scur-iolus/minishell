/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:18:11 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/19 18:21:55 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear_pipe(t_pipe *this, t_data *data)
{
	int i;
	int j;

	i = -1;
	j = ft_lstsize(data->cmd) + 1;

	if (this->end)
	{
		while (this->end[++i] < j)
				free(this->end[i]);
		free(this->end);
	}
	free(this);
}
