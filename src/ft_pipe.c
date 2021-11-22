/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:18:11 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/22 20:19:45 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear_pipe(t_pipe *this)
{
	if (this->path)
		ft_free_split(this->path);
	// TODO check if this->end is on the heap
	free(this);
}
