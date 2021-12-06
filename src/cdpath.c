/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:23:36 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/06 11:44:17 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*make_path(char *cdpath, char *cmd)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(cdpath, "/");
	if (!temp)
	{
		ft_error(MALLOC_ERROR);
		return (NULL);
	}
	path = ft_strjoin(temp, cmd);
	free(temp);
	if (!path)
	{
		ft_error(MALLOC_ERROR);
		return (NULL);
	}
	return (path);
}

static void	print_cdpath_cmd(char *cdpath, char *arg)
{
	if (cdpath[0] == '/')
	{
		if (!cdpath[1])
		{
			ft_putstr_fd("/", 1);
			ft_putstr_fd(arg, 1);
			ft_putstr_fd("\n", 1);
		}
	}
}

static t_bool	cdpath_check_every_path(t_data *data, char **cdpath, char **cmd, char *path)
{
	int	i;

	i = -1;
	while (cdpath[++i])
	{
		path = make_path(cdpath[i], cmd[1]);
		if (!chdir(path))
		{
			print_cdpath_cmd(cdpath[i], cmd[1]);
			change_directory(data);
			free(path);
			ft_free_split(cdpath);
			return (1);
		}
		free(path);
	}
	return (0);
}

t_bool	cdpath(t_data *data, char **cmd)
{
	t_env	*temp;
	char	**cdpath;
	char	*path;
	int		i;

	i = -1;
	temp = find_var_env(data, "CDPATH");
	cdpath = ft_split(temp->value, ':');
	if (!(cdpath))
	{
		err_free(MALLOC_ERROR, data, 0);
		return (1);
	}
	if (cmd[1])
	{
		if (cdpath_check_every_path(data, cdpath, cmd, path))
			return (1);
	}
	ft_free_split(cdpath);
	return (0);
}
