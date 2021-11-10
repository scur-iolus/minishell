/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:12:34 by llalba            #+#    #+#             */
/*   Updated: 2021/11/10 15:46:01 by llalba           ###   ########.fr       */
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
** Sur la heap: line, data->env_lst, *output, var_name
*/

static void	add_var_value(char **output, char *var_name, t_data *data)//CHECKED
{
	size_t	value_len;
	size_t	insertion_position;
	t_env	*node;

	node = find_var_env(data, var_name);
	if (!node)
		return ;
	value_len = ft_strlen(node->value);
	insertion_position= ft_strlen(*output);
	if (!ft_str_insert_str(output, node->value, insertion_position, value_len))
		err_free(0, data, *output, var_name);
}

/*
** Sur la heap: line, data->env_lst, *output
*/

static void	replace_var(t_data *data, char **output, size_t *position)//CHECKED
{
	size_t	name_len;
	char	*var_name;
	size_t	i;

	name_len = get_var_name_len(data->line + (*position));
	if (name_len == 0)
	{
		(*position) += special_cases(data, output, position);
		return ;
	}
	var_name = (char *) ft_calloc(name_len + 1, sizeof(char));
	if (!var_name)
		err_free(0, data, *output, 0);
	i = 0;
	while (i < name_len)
	{
		var_name[i] = *(data->line + (*position) + i);
		i++;
	}
	add_var_value(output, var_name, data);
	(*position) += name_len;
	free(var_name);
}

/*
** Sur la heap: line, data->env_lst, *output
*/

static void	next(t_data *data, char **output, short *between, size_t *position)//CHECKED
{
	char	c;

	c = data->line[*position];
	if (c == '\'')
		*between = !(*between);
	if (c == '$' && !(*between))
	{
		(*position)++;
		replace_var(data, output, position);
	}
	else
	{
		if (!ft_str_insert_char(output, c, position))
			err_free(0, data, *output, 0);
		(*position)++;
	}
}

/*
** Sur la heap: line, data->env_lst
*/

char	*convert_env_var(t_data *data)//CHECKED
{
	char	*new;
	size_t	position;
	short	between_apostrophes;

	new = (char *) malloc(0);
	if (!new)
		err_free(0, data, 0, 0);
	position = 0;
	between_apostrophes = 0;
	while (data->line[position])
		next(data, &new, &between_apostrophes, &position);
	free(data->line);
	return (new);
}
