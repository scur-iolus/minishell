/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:44:53 by llalba            #+#    #+#             */
/*   Updated: 2021/11/30 12:14:53 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fill_in_str(t_env *src, char *dest, size_t var_len, size_t value_len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < var_len)
	{
		dest[i] = (src->var)[i];
		i++;
	}
	dest[var_len] = '=';
	i = var_len + 1;
	j = 0;
	while (j < value_len)
	{
		dest[i] = (src->value)[j];
		i++;
		j++;
	}
	return (dest);
}

size_t	get_lst_len(t_env *head)
{
	size_t	len;

	len = 0;
	while (head)
	{
		len++;
		head = head->next;
	}
	return (len);
}

char	**list_to_env(t_env *lst_head) //NOTA BENE peut etre rajouter la notion -> if is_env
{
	char	**head;
	size_t	i;
	size_t	var_len;
	size_t	value_len;

	head = (char **) ft_calloc(get_lst_len(lst_head) + 1, sizeof(char *));
	if (!head)
		exit(1); // malloc fail, free et exit à coder proprement
	i = 0;
	while (lst_head)
	{
		var_len = ft_strlen(lst_head->var);
		value_len = ft_strlen(lst_head->value);
		head[i] = (char *) ft_calloc(var_len + value_len + 2, sizeof(char));
		if (!(head[i]))
			exit(1); // malloc fail, free et exit à coder proprement
		head[i] = fill_in_str(lst_head, head[i], var_len, value_len);
		lst_head = lst_head->next;
		i++;
	}
	head[i] = 0;
	return (head);
}
