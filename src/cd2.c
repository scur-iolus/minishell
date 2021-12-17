/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:33:11 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/17 13:46:37 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_directory(t_data *data, char *line)
{
	switch_old_pwd(data, line);
	switch_pwd(data, line);
}

t_bool	arg_is_point_point(char *str)
{
	if (str[0] == '.')
	{
		if (str[1] == '.')
		{
			if (!str[2])
				return (1);
		}
	}
	if (str[0] == '.')
	{
		if (!str[1])
			return (1);
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

int	go_to_old_pwd(t_data *data, char **cmd)
{
	char	line[PATH_MAX];
	t_env	*env;
	int		j;

	j = -1;
	while (++j < PATH_MAX)
		line[j] = 0;
	env = find_var_env(data, "OLDPWD");
	if (!env)
	{
		ft_error("OLD_PWD is not set");
		return (1);
	}
	getcwd(line, PATH_MAX);
	if (!chdir(env->value))
	{
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\n", 1);
		change_directory(data, line);
		return (0);
	}
	ft_error(FILE_NOT_FOUND);
	return (1);
}
