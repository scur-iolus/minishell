/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:13:03 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/09 14:55:18 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstadd_front(t_cmd **alst, t_cmd *new)
{
	t_cmd	*temp;

	temp = *alst;
	*alst = new;
	new->next = temp;
}
