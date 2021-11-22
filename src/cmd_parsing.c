/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/22 20:23:07 by llalba           ###   ########.fr       */
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
	free(head->cmd);
	head->cmd = new_split;
}

/*
void	parse_cmd(t_data *data, char *cmd_line) // ici la fonction va créer la nouvelle liste cmd en remplissant cmd et cmd_path
{
	//cmd_line = string de la commande avec ses arguments. ex : cat -e  ou head -1
	int		i;
	t_cmd	*new;

	new->cmd = ft_split(cmd_line, ' ');
	if (!new->cmd)
		free_all(data, 1);
	find_command_path(data, new, cmd_line);
	ft_lstadd_back(data->cmd, new);
}

Pour un > :
data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
Pour un >> :
data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
Pour un < :
data->infile = open(argv[1], O_RDONLY);
Pour un << :
data->here_doc = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);

static int	check_next()
{

}

static int	check_previous()
{

}

*/

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw, data->cmd->split
** update_data() and categorize() have 3 possible outputs:
**			0, the "word" belongs to the command itself
**			1, this file could not be opened
**			2, openable and possibly already closed, if not, added to data
*/

static int	update_data(t_data *data, t_cmd *head, size_t i, short category)
{
	int	closed;

	if (category == ONE_RIGHT || category == TWO_RIGHT || category == ONE_LEFT)
	{
		if (!open_file(head, (head->split)[i], category))
			return (1);
		return (2);
	}
	closed = 0;
	if (category == TWO_LEFT && head->infile > 0)
	{
		closed = close(head->infile);
		if (closed == -1)
			ft_error(FAILED_TO_CLOSE);
	}
	if (category == TWO_LEFT)
		head->infile = -1;
	add_str_to_cmd(data, head, i);
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw, data->cmd->split
** update_data() and categorize() have 3 possible outputs:
**			0, the "word" belongs to the command itself
**			1, this file could not be opened
**			2, openable and possibly already closed, if not, added to data
*/

static int	categorize(t_data *data, t_cmd *head, size_t i)
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
	return (update_data(data, head, i, category));
}

/*
** On the heap: line, data->env_lst, data->cmd, data->cmd->raw, data->cmd->split
*/

short	parse_cmd_content(t_data *data, t_cmd *head)
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
		{
			ft_error(NOT_FOUND);
			return (0);
		}
		i++;
	}

	// FIXME ===============
	char	**hop;//FIXME
	hop = head->cmd;//FIXME
	while (*hop)//FIXME
	{//FIXME
		printf("🔸%s🔸\n", *hop); // FIXME ===============
		hop++;//FIXME
	}//FIXME
	ft_exit(data, 0, 0, 0); //FIXME
	return (1);//CHECKED
}
