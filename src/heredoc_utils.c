/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:06:57 by llalba            #+#    #+#             */
/*   Updated: 2021/12/14 12:43:50 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_bool	is_dollar_heredoc(char *str, size_t i)
{
	t_bool	between_quotes;
	t_bool	between_apo;
	int		left_chevron;
	size_t	j;

	between_quotes = 0;
	between_apo = 0;
	left_chevron = 0;
	j = 0;
	while (j != i)
	{
		if (str[j] == '\'' && !between_quotes)
			between_apo = !between_apo;
		else if (str[j] == '\"' && !between_apo)
			between_quotes = !between_quotes;
		if (!between_apo && !between_quotes && str[j] == '<')
			left_chevron++;
		else if (!between_apo && !between_quotes && str[j] != ' ')
			left_chevron = 0;
		j++;
	}
	if (left_chevron == 2)
		return (1);
	return (0);
}

void	protect_with_backslash(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == '$' && is_dollar_heredoc(data->line, i))
			data->line[i] = '\\';
		i++;
	}
}

void	replace_backslash(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == '\\')
			data->line[i] = '$';
		i++;
	}
}

t_bool	load_delimiter(char *new, char *str)
{
	size_t	i;

	if (ft_strlen(str) > DELIMITER_LEN)
	{
		write(2, HEREDOC_LEN, ft_strlen(HEREDOC_LEN));
		return (0);
	}
	i = 0;
	while (*str)
	{
		new[i] = *str;
		str++;
		i++;
	}
	new[i] = '\n';
	new[i + 1] = '\0';
	return (1);
}
