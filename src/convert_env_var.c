/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:12:34 by llalba            #+#    #+#             */
/*   Updated: 2021/10/11 18:47:09 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

short	to_be_interpreted(char *dollar, char *line)
{

	return (1);
}

void	check_next_char(char *line, size_t *position, char *output)
{



		to_be_interpreted(ft_strchr(line, (int) '$'), line)
		len = ft_strlen(line);
		output = ft_calloc(len, sizeof(char));
		if (!output)
			exit (1); // malloc fail, free et exit à coder proprement
}

char	*convert_env_var(t_env *env_lst, char *line)
{
	char	*output;
	size_t	position;

	output = (char *) malloc(0);
	position = 0;
	while (line[position])
		check_next_char(line, &position, output);
	free(line);
	return (output);
}

/*

\ ; unclosed quotes
$$
$?
$VAR
$nimp donne rien
| < > << >>

*/