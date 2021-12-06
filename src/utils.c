/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:14:43 by llalba            #+#    #+#             */
/*   Updated: 2021/12/06 11:39:22 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
}

static t_bool	close_previous(t_cmd *head, char *file, t_bool opening)
{
	int	fail;

	fail = 0;
	if (head->infile && opening == ONE_LEFT)
		fail = close(head->infile);
	else if (head->outfile && (opening == ONE_RIGHT || opening == TWO_RIGHT))
		fail = close(head->outfile);
	if (fail == -1)
	{
		ft_error(CLOSE_FAILED);
		return (0);
	}
	return (1);
}

t_bool	open_file(t_cmd *head, char *file, t_bool opening)
{
	int	fd;

	if (!close_previous(head, file, opening))
		return (0);
	fd = 0;
	if (opening == ONE_RIGHT)
		fd = open (file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (opening == TWO_RIGHT)
		fd = open (file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (opening == ONE_LEFT)
		fd = open (file, O_RDONLY);
	if (fd == -1)
	{
		ft_error(FILE_NOT_FOUND);
		return (0);
	}
	if (opening == ONE_LEFT)
		head->infile = fd;
	if (opening == ONE_RIGHT || opening == TWO_RIGHT)
		head->outfile = fd;
	return (1);
}

void	update_var_shlvl(t_data *data)
{
	t_env	*temp;
	int		i;

	temp = find_var_env(data, "SHLVL");
	if (temp)
	{
		i = ft_atoi(temp->value);
		i++;
		free(temp->value);
		temp->value = ft_itoa(i);
		if (!temp->value)
			ft_error(MALLOC_ERROR);
	}
}
