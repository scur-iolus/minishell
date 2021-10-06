/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:56:09 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/09/28 14:55:38 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static char	*save_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	line[i] = '\0';
	return (line);
}

static char	*save_rest(char *save)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	ret = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!ret)
		return (NULL);
	while (save[++i])
		ret[j++] = save[i];
	ret[j] = '\0';
	free(save);
	save = NULL;
	return (ret);
}

static int	nextline(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == '\n')
			return (1);
	return (0);
}

static int	result(int ret, char **line, char **save)
{
	*line = save_line(*save);
	*save = save_rest(*save);
	if (*save == NULL)
	{
		free (*save);
		*save = NULL;
	}
	if (ret == 0 && *save == NULL)
	{
		free(*line);
		return (0);
	}
	return (1);
}

//GNL special pour pipex avec un free line si ret == 0 et un flag
// pour free save

int	get_next_line(int fd, char **line, int flag)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*save;
	int			ret;

	if (flag && save)
	{
		if (save)
			free(save);
		return (0);
	}
	ret = 1;
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	while (!nextline(save) && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (-1);
		buff[ret] = '\0';
		if (!save)
			save = ft_strdup(buff);
		else
			save = ft_strjoin_get_next_line(save, buff);
	}
	return (result(ret, line, &save));
}
