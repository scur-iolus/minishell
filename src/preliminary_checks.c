/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:26:32 by llalba            #+#    #+#             */
/*   Updated: 2021/10/19 16:21:46 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	split_n_join(char **line)
{
	char	**line_split;
	char	**tmp;
	size_t	i;

	line_split = ft_split(*line, '"');
	if (!line_split)
		exit(1); // TODO: malloc fail, free et exit à coder proprement
	free(*line);
	tmp = line_split;
	i = 1;
	while (line_split[0] && line_split[i])
	{
		*line = ft_strjoin(line_split[0], line_split[i]);
		if (!(*line))
			exit(1); // TODO: malloc fail, free et exit à coder proprement
		free(line_split[0]);
		free(line_split[i]);
		line_split[0] = *line;
		i++;
	}
	free(tmp);
}

static void	remove_quotation_marks(char **line)
{
	size_t	i;
	long	apostrophes;

	i = 0;
	apostrophes = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'')
			apostrophes++;
		else if ((*line)[i] == '\"' && apostrophes % 1 == 0)
			(*line)[i] = ';';
		i++;
	}
	if (ft_strchr(*line, (int) '\"'))
		split_n_join(line);
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == ';')
			(*line)[i] = '\"';
		i++;
	}
}

static short	line_is_valid(char *line)
{
	long	apostrophes;
	long	quote_marks;

	apostrophes = 0;
	quote_marks = 0;
	while (*line)
	{
		if ((*line) == '\\' || (*line) == ';')
			return (0);
		else if ((*line) == '\'' && quote_marks % 2 == 0)
			apostrophes++;
		else if ((*line) == '\"' && apostrophes % 2 == 0)
			quote_marks++;
		line++;
	}
	if (apostrophes % 2 == 1 || quote_marks % 2 == 1)
		return (0);
	return (1);
}

static void	remove_comment(char **line)
{
	size_t	len;
	char	*output;
	short	btwn_apo;

	len = 0;
	btwn_apo = 0;
	while ((*line)[len] && ((*line)[0] != '#'))
	{
		if ((*line)[len] == '\'')
			btwn_apo = !btwn_apo;
		if (len && (*line)[len] == '#' && (*line)[len - 1] == ' ' && !btwn_apo)
		{
			len--;
			break ;
		}
		len++;
	}
	output = calloc(len + 1, sizeof(char));
	while (len)
	{
		output[len - 1] = (*line)[len - 1];
		len--;
	}
	free(*line);
	(*line) = output;
}

void	preliminary_checks(char **line, t_data *data, char **env)
{
	char	*tmp;

	if (ft_strlen(*line) > 0 && ft_strchr(*line, (int) '#'))
		remove_comment(line);
	if (ft_strlen(*line) > 0 && !line_is_valid(*line))
	{
		write(1, INVALID_CHAR_ERR, ft_strlen(INVALID_CHAR_ERR));
		return ;
	}
	data->env_lst = init_env(env);
	*line = convert_env_var(data, *line);
	if (**line != '\0')
		remove_quotation_marks(line);
	tmp = *line;
	*line = ft_strtrim(*line, " 	");
	free(tmp);
}