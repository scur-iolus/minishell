/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_special_cases.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:06:57 by llalba            #+#    #+#             */
/*   Updated: 2021/12/03 17:45:16 by llalba           ###   ########.fr       */
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
