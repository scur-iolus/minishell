/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:14:06 by llalba            #+#    #+#             */
/*   Updated: 2021/11/17 18:10:08 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** On the heap: line, data->env_lst, cmd_split
*/

static void	add_str_to_cmd(t_data *data, t_cmd *head, char *str, char **split)//CHECKED
{
	char	*to_add;
	char	**new_split;
	size_t	len;

	to_add = ft_strdup(str);
	if (!to_add)
		err_free(0, data, 0, split);
	len = ft_strlen_split(head->cmd);
	new_split = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!new_split)
		err_free(0, data, to_add, split);
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
data->here_doc = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);




*/

static int	categorize(char **split, char *current)
{
	int				status;
	static short	was_left_chevron = 0;
	// TODO static short	next_is_right_chevron = 0;

	status = 0;
	while (*split && *split != current)
	{
		if (!ft_strcmp("<", *split))
			was_left_chevron = !was_left_chevron;

		*split = split++;
	}
	if (was_left_chevron)
	{
		if (!file_can_be_opened(*split))
			return (1);
		return (2);
	}


	return (status);
}

/*
** On the heap: line, data->env_lst
*/

short	parse_cmd_content(t_data *data, t_cmd *head)
{
	char	**cmd_split;
	char	**tmp;
	int		status;

	cmd_split = ft_split(head->raw, ' ');
	if (!cmd_split)
		err_free(0, data, 0, 0);
	tmp = cmd_split;
	status = 0;
	while (*cmd_split)
	{
		status = categorize(tmp, *cmd_split);
		if (status == 0)
			add_str_to_cmd(data, head, *cmd_split, tmp);
		else if (status == 1)
		{
			ft_error(NOT_FOUND);
			ft_free_split(tmp);
			return (0);
		}
		cmd_split++;
	}

	// FIXME ===============
	char	**hop;//FIXME
	hop = head->cmd;//FIXME
	while (*hop)//FIXME
	{//FIXME
		printf("🔸%s🔸\n", *hop); // FIXME ===============
		hop++;//FIXME
	}//FIXME
	ft_free_split(tmp);//CHECKED
	ft_exit(data, 0, 0, 0); //FIXME
	return (1);//CHECKED
}
