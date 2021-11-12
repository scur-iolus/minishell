/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:18:11 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/12 13:26:20 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear_pipe(t_pipe *this)
{
	if (this->path)
		ft_free_split(this->path);
	// TODO check if this->end is on the heap
	if (this->infile)
		free(this->infile);
	if (this->outfile)
		free(this->outfile);
	free(this);
}