/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 09:48:53 by llalba            #+#    #+#             */
/*   Updated: 2021/12/20 17:15:32 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	opening_or_closing(t_bool between)
{
	if (!between)
		return (3);
	return (2);
}

/*
** Returns 1 when the character i is between ' or "
** Returns 2 when the character i is an opening ' or a " AND not between ' or "
** Returns 3 when the character i is a closing ' or a " AND not between ' or "
** Else, returns 0
*/

int	quote_status(char *str, size_t i)
{
	size_t	j;
	t_bool	between_apo;
	t_bool	between_quotes;

	j = -1;
	between_apo = FALSE;
	between_quotes = FALSE;
	while (str[++j])
	{
		if (str[j] == '\'' && !between_quotes)
		{
			between_apo = !between_apo;
			if (j == i)
				return (opening_or_closing(between_apo));
		}
		else if (str[j] == '\"' && !between_apo)
		{
			between_quotes = !between_quotes;
			if (j == i)
				return (opening_or_closing(between_quotes));
		}
		if (j == i && (between_quotes || between_apo))
			return (1);
	}
	return (0);
}

void	secure_between(char *str, char to_secure, char tmp, t_bool remove)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (remove && str[i] == tmp && quote_status(str, i) == 1)
			str[i] = to_secure;
		if (!remove && str[i] == to_secure && quote_status(str, i) == 1)
			str[i] = tmp;
		i++;
	}
}

char	*str_without_quotes(char **str)
{
	size_t	new_len;
	size_t	i;
	char	*new;

	new_len = 0;
	i = 0;
	while ((*str)[i])
	{
		if (quote_status(*str, i) < 2)
			new_len++;
		i++;
	}
	new = (char *)ft_calloc(new_len + 1, sizeof(char));
	return (new);
}

t_bool	remove_surrounding_quotes(char **str)
{
	char	*new;
	size_t	str_i;
	size_t	new_i;

	new = str_without_quotes(str);
	if (!new)
		return (0);
	str_i = 0;
	new_i = 0;
	while ((*str)[str_i])
	{
		if (quote_status(*str, str_i) < 2)
		{
			new[new_i] = (*str)[str_i];
			new_i++;
		}
		str_i++;
	}
	free(*str);
	*str = new;
	return (1);
}
