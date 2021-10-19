/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:12:34 by llalba            #+#    #+#             */
/*   Updated: 2021/10/19 16:57:36 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	get_var_name_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '$' && \
		str[i] != '|' && str[i] != '?' && str[i] != ' ' && str[i] != '.')
		i++;
	return (i);
}

static void	add_var_value(char **output, char *var_name, t_data *data)
{
	char	*new;
	size_t	value_len;
	size_t	i;
	t_env	*node;

	node = find_var_env(data, var_name);
	if (!node)
		return ;
	value_len = ft_strlen(node->value);
	new = (char *) ft_calloc(ft_strlen(*output) + value_len + 1, sizeof(char));
	if (!new)
		exit (1); // TODO: malloc fail, free et exit à coder proprement
	i = 0;
	while ((*output)[i])
	{
		new[i] = (*output)[i];
		i++;
	}
	while (value_len)
	{
		new[i + value_len - 1] = node->value[value_len];
		value_len--;
	}
	free(*output);
	*output = new;
}

static void	replace_var(char **output, char *line, size_t *pos, t_data *data)
{
	size_t	name_len;
	char	*var_name;
	size_t	i;

	(*pos)++;
	name_len = get_var_name_len(line + (*pos));
	if (!name_len)
	{
		(*pos) += add_special_case(output, line, pos, data);
		return ;
	}
	var_name = (char *) ft_calloc(name_len + 1, sizeof(char));
	if (!var_name)
		exit (1); // TODO: malloc fail, free et exit à coder proprement
	i = 0;
	while (i < name_len)
	{
		var_name[i] = *(line + (*pos) + i);
		i++;
	}
	add_var_value(output, var_name, data);
	(*pos) += name_len;
	free(var_name);
}

void	add_one_char(char **old, char *line, size_t *position, int c)
{
	char	*new;
	size_t	i;

	new = (char *) ft_calloc(ft_strlen(*old) + 2, sizeof(char));
	if (!new)
		exit (1); // TODO: malloc fail, free et exit à coder proprement
	i = 0;
	while ((*old)[i])
	{
		new[i] = (*old)[i];
		i++;
	}
	if (c)
		new[i] = c;
	else
	{
		new[i] = line[*position];
		(*position)++;
	}
	free(*old);
	*old = new;
}

char	*convert_env_var(t_data *data, char *line)
{
	char	*output;
	size_t	position;
	short	between_apostrophes;

	output = (char *) malloc(0);
	position = 0;
	between_apostrophes = 0;
	while (line[position])
	{
		if (line[position] == '\'')
			between_apostrophes = !between_apostrophes;
		if (line[position] == '$' && !between_apostrophes)
			replace_var(&output, line, &position, data);
		else
			add_one_char(&output, line, &position, 0);
	}
	free(line);
	return (output);
}
