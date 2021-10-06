/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:05:18 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/06 16:07:45 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	take_env(t_data *data, char **env)
{
	char	*key_path;
	int		key_path_len;
	int		i;
	int		j;

	j = -1;
	i = -1;
	key_path = "PATH=";
	key_path_len = ft_strlen(key_path);
	while (env[++i])
		if (ft_strncmp(key_path, env[i], key_path_len) == 0)
			break ;
	while (++j < key_path_len)
		env[i]++;
	data->path = ft_split(env[i], ':');
}

void	parse_cmd(int argc, char **argv, t_data *data)
{
	int		i;
	t_list	*new;

	i = 1 + data->flag_hd;
	while (++i < argc - 1)
	{
		data->cmd = ft_split(argv[i], ' '); // ici il faut remplacer argv[i] par la string de la commande 
		if (!data->cmd)
			free_all_failure(data);
		new = ft_lstnew(data->cmd);
		find_command_path(data, new);
		ft_lstadd_back(&data->list, new);
	}
}

void	find_command_path(t_data *data, t_list *list)
{
	int		i;
	int		h;
	char	*tmp;

	i = -1;
	while (data->path[++i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		list->cmd_path = ft_strjoin(tmp, data->cmd[0]);
		free(tmp);
		h = access(list->cmd_path, F_OK);
		if (!h)
			break ;
		else
		{
			free(list->cmd_path);
			list->cmd_path = NULL;
		}
	}
}

t_list	*select_list(int cmd_numb, t_data *data)
{
	t_list	*temp;
	int		j;

	temp = data->list;
	j = 0;
	while (++j < cmd_numb && temp)
		temp = temp->next;
	return (temp);
}

void	print_list(t_data *data)
{
	t_list	*temp;
	int		i;
	int		j;

	j = 0;
	temp = data->list;
	while (temp)
	{
		i = -1;
		ft_putstr_fd("==CMD ", 2);
		ft_putnbr_fd(++j, 2);
		ft_putstr_fd("==\n\n", 2);
		while (temp->cmd[++i])
		{
			ft_putstr_fd(temp->cmd[i], 2);
			ft_putstr_fd("\n", 2);
		}
		ft_putstr_fd("PATH --> ", 2);
		ft_putstr_fd(temp->cmd_path, 2);
		ft_putstr_fd("\n\n", 2);
		temp = temp->next;
	}
}
