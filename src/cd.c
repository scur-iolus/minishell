/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:32:59 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/03 17:10:34 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	error_ft_cd(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			ft_error(INVALID_OPTION);
			return (1);
		}
		while (cmd[i])
			i++;
		i--;
		if (i > 1)
		{
			ft_error(TOO_MANY_ARG2);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	switch_old_pwd(t_data *data, char *line)
{
	t_env	*env;

	env = NULL;
	env = find_var_env(data, "OLDPWD");
	if (!env)
		return ;
	free(env->value);
	env->value = ft_strdup(line);
	if (!env->value)
	{
		ft_error(MALLOC_ERROR);
		chdir(line);
	}
}

void	switch_pwd(t_data *data, char *line)
{
	t_env	*env;
	char	*old_dir;

	env = NULL;
	old_dir = ft_strdup(line);
	if (!old_dir)
	{
		ft_error(MALLOC_ERROR);
		return ;
	}
	getcwd(line, PATH_MAX);
	env = find_var_env(data, "PWD");
	if (!env)
		return ;
	free(env->value);
	env->value = ft_strdup(line);
	if (!env->value)
	{
		env = find_var_env(data, "OLDPWD");
		free(env->value);
		env->value = ft_strdup(old_dir);
		chdir(old_dir);
	}
	free(old_dir);
}

static int	go_to_home(t_data *data)
{
	char	line[PATH_MAX];
	t_env	*env;

	env = find_var_env(data, "HOME");
	if (!env)
	{
		ft_error(HOME_NOT_SET);
		return (1);
	}
	getcwd(line, PATH_MAX);
	if (env->value[0] == '\0')
		return (0);
	if (!chdir(env->value))
	{
		switch_old_pwd(data, line);
		switch_pwd(data, line);
	}
	else
	{
		ft_error(FILE_NOT_FOUND);
		return (1);
	}
	return (0);
}

t_bool	ft_cd(t_data *data, char **cmd)
{
	if (error_ft_cd(cmd))
		return (1);
	if (find_var_env(data, "CDPATH") && cmd[1])
	{
		if (!arg_is_point_point(cmd[1]))
			if (cdpath(data, cmd))
				return (0);
	}
	if (cmd[1])
	{
		if (!chdir(cmd[1]))
			change_directory(data);
		else
		{
			ft_error(FILE_NOT_FOUND);
			return (1);
		}
	}
	else
	{
		if (go_to_home(data))
			return (1);
	}
	return (0);
}
