/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/12/01 11:31:38 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw, data->cmd->split
*/

static void	add_str_to_cmd(t_data *data, t_cmd *head, size_t i)//CHECKED
{
	char	*to_add;
	char	**new_split;
	size_t	len;

	to_add = ft_strdup((head->split)[i]);
	if (!to_add)
		err_free(MALLOC_ERROR, data, 0);
	len = ft_strlen_split(head->cmd);
	new_split = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!new_split)
		err_free(MALLOC_ERROR, data, to_add);
	new_split[len] = to_add;
	while (len)
	{
		new_split[len - 1] = (head->cmd)[len - 1];
		len--;
	}
	if (head->cmd)
		free(head->cmd);
	head->cmd = new_split;
}

static short	heredoc_is_last(t_cmd *head)//CHECKED
{
	size_t	i;
	int		closed;

	if (*(head->split) == 0)
		return (1);
	i = ft_strlen_split(head->split) - 1;
	closed = 0;
	while (i && !ft_strrchr((head->split)[i], '<'))
		i--;
	if (!ft_strcmp((head->split)[i], "<<") && head->infile)
	{
		closed = close(head->infile);
		if (closed == -1)
		{
			ft_error(FAILED_TO_CLOSE);
			return (0);
		}
	}
	else if (!ft_strcmp((head->split)[i], "<") && head->heredoc)
	{
		free(head->heredoc);
		head->heredoc = 0;
	}
	return (1);
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw, data->cmd->split
** update_data() and categorize() have 3 possible outputs:
**			0, the "word" belongs to the command itself (head, cat, -e, -1)
**			1, this file could not be opened
**			2, openable and possibly already closed, if not, added to data
*/

static int	ret_categorize(t_data *data, t_cmd *head, size_t i, short category)//CHECKED
{
	char	*str;

	str = (head->split)[i];
	if (category == ONE_RIGHT || category == TWO_RIGHT || category == ONE_LEFT)
	{
		if (!open_file(head, str, category))
			return (1);
		return (2);
	}
	if (!category && !ft_strrchr(str, '<') && !ft_strrchr(str, '>'))
		return (0);
	return (2);
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw, data->cmd->split
** update_data() and categorize() have 3 possible outputs:
**			0, the "word" belongs to the command itself (head, cat, -e, -1)
**			1, this file could not be opened
**			2, openable and possibly already closed, if not, added to data
*/

static int	categorize(t_data *data, t_cmd *head, size_t i)//CHECKED
{
	short	category;
	char	**tmp;

	category = 0;
	tmp = head->split;

	while (*tmp && *tmp != (head->split)[i])
	{
		if (!ft_strcmp(">", *tmp))
			category = ONE_RIGHT;
		else if (!ft_strcmp(">>", *tmp))
			category = TWO_RIGHT;
		else if (!ft_strcmp("<", *tmp))
			category = ONE_LEFT;
		else if (!ft_strcmp("<<", *tmp))
			category = TWO_LEFT;
		else
			category = 0;
		tmp++;
	}
	return (ret_categorize(data, head, i, category));
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw, data->cmd->split
*/

short	parse_cmd_content(t_data *data, t_cmd *head)//CHECKED
{
	size_t	i;
	int		status;

	i = 0;
	status = 0;
	while ((head->split)[i])
	{
		status = categorize(data, head, i);
		if (status == 0)
			add_str_to_cmd(data, head, i);
		else if (status == 1)
			return (0);
		i++;
	}
	if (head->cmd)
		find_command_path(data, head);
	// FIXME ===============
	// char	**hop;//FIXME
	// hop = head->cmd;//FIXME
	// while (hop && *hop)//FIXME
	// {//FIXME
	// 	printf("🔸%s🔸\n", *hop); // FIXME ===============
	// 	hop++;//FIXME
	// }//FIXME
	// printf("💫 fd infile : %d\n", head->infile); // FIXME ===============
	// printf("💫 fd outfile : %d\n", head->outfile); // FIXME ===============
	// printf("💫 cmd_path : %s\n", head->cmd_path); // FIXME ===============
	// printf("💫 [heredoc] : [%s]\n", head->heredoc); // FIXME ===============
	return (heredoc_is_last(head));
}
