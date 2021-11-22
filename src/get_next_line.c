/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:01:40 by llalba            #+#    #+#             */
/*   Updated: 2021/11/22 20:08:38 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*save_line(char *str)//CHECKED
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (0);
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	return (line);
}

static char	*save_remainder(char *save)//CHECKED
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	ret = (char *)ft_calloc(ft_strlen(save) - i, sizeof(char));
	if (!ret)
		return (0);
	while (save[++i])
		ret[j++] = save[i];
	return (ret);
}

short	contains_new_line(char *str)//CHECKED
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

/*
** 3 possibles return values for gnl_result:
** -> 0 if the user pressed Ctrl D or entered a '\0' somehow (end of stdin)
** -> -1 if an error occurred (either malloc returned 0 or read returned -1)
** -> else, 1
*/

int	gnl_result(int ret, char **line, char **save)//CHECKED
{
	char *tmp;

	if (ret < 0)
		return (-1);
	else if (ret == 0)
		return (0);
	*line = save_line(*save);
	if (*line == 0)
		return (-1);
	tmp = *save;
	*save = save_remainder(*save);
	free(tmp);
	tmp = 0;
	if (*save == 0)
		return (-1);
	return (1);
}
