/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:12:34 by llalba            #+#    #+#             */
/*   Updated: 2021/11/11 18:47:23 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	get_var_name_len(char *str)//CHECKED
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '$' && \
		str[i] != '|' && str[i] != '?' && str[i] != ' ' && str[i] != '.')
		i++;
	return (i);
}

/*
** On the heap: line, data->env_lst, *new, var_name
*/

static void	add_var_value(char **new, char *var_name, t_data *data)//CHECKED
{
	size_t	value_len;
	size_t	insertion_position;
	t_env	*node;

	node = find_var_env(data, var_name);
	if (!node)
		return ;
	insertion_position= ft_strlen(*new);
	if (!ft_str_insert_str(new, node->value, insertion_position))
		err_free(0, data, *new, var_name);
}

/*
** On the heap: line, data->env_lst, *new
*/

static void	replace_var(t_data *data, char **new, size_t *position)//CHECKED
{
	size_t	name_len;
	char	*var_name;
	size_t	i;

	name_len = get_var_name_len(data->line + (*position));
	if (name_len == 0)
	{
		(*position) += special_cases(data, new, position);
		return ;
	}
	var_name = (char *) ft_calloc(name_len + 1, sizeof(char));
	if (!var_name)
		err_free(0, data, *new, 0);
	i = 0;
	while (i < name_len)
	{
		var_name[i] = *(data->line + (*position) + i);
		i++;
	}
	add_var_value(new, var_name, data);
	(*position) += name_len;
	free(var_name);
}

/*
** On the heap: line, data->env_lst, *new
*/

static void	next(t_data *data, char **new, short *between, size_t *position)//CHECKED
{
	char	c;

	c = data->line[*position];
	if (c == '\'')
		*between = !(*between);
	if (c == '$' && !(*between))
	{
		(*position)++;
		replace_var(data, new, position);
	}
	else
	{
		if (!ft_str_insert_char(new, c, *position))
			err_free(0, data, *new, 0);
		(*position)++;
	}
}

/*
** On the heap: line, data->env_lst
*/

char	*convert_env_var(t_data *data)//CHECKED
{
	char	*new;
	size_t	position;
	short	between_apostrophes;

	new = (char *) ft_calloc(1, sizeof(char));
	if (!new)
		err_free(0, data, 0, 0);
	position = 0;
	between_apostrophes = 0;
	while (data->line[position])
		next(data, &new, &between_apostrophes, &position);
	free(data->line);
	return (new);
}
