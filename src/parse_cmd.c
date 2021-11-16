/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/16 16:09:26 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst
*/

static void	parse_cmd_content(t_data *data, t_cmd *head)
{
	char		**cmd_split;
	char		**tmp;

	cmd_split = ft_split(head->raw, ' ');
	if (!cmd_split)
		err_free(0, data, 0, 0);
	tmp = cmd_split;
	while (*cmd_split)
	{
		printf("🔸%s", *cmd_split); // FIXME ===============
		// TODO ici
		cmd_split++;
	}
	printf("🔸"); // FIXME ===============
	ft_free_split(tmp);
}

/*
** On the heap: line, data->env_lst, and progressively data->cmd
*/

static void	pipes_split_raw(t_data *data, t_cmd **head)//CHECKED
{
	char	**ptr;
	t_cmd	*new;
	char	*trimmed;
	size_t	i;

	i = 0;
	ptr = ft_split(data->line, '|');
	if (!ptr)
		err_free(MALLOC_ERROR, data, 0, 0);
	while (ptr[i])
	{
		trimmed = ft_strtrim(ptr[i], " 	");
		free(ptr[i]);
		if (!trimmed)
			err_free(MALLOC_ERROR, data, 0, 0);
		new = ft_lstnew_cmd(trimmed);
		if (!new)
			err_free(MALLOC_ERROR, data, trimmed, 0);
		cmd_add_back(head, new);
		data->cmd = *head;
		i++;
	}
	data->cmd = *head;
}

/*
** On the heap: line, data->env_lst
** This func also checks that there isn't any | followed by spaces and another |
** In that case, an error is raised and the function returns
*/

void	parse_cmd_list(t_data *data)
{
	t_cmd	*head;

	head = 0;
	pipes_split_raw(data, &head);
	while (head)
	{
		if (ft_strchr(data->line, '|') && *(head->raw) == '\0')
		{
			ft_error(INVALID_CHAR_ERR);
			return ;
		}
		parse_cmd_content(data, head);
		head = head->next;
		printf("\n");//FIXME
	}
}
