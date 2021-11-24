/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:32:59 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/24 12:02:41 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

short	ft_cd(t_data *data, char **cmd)
{
	char line[PATH_MAX];
	char *temp;

	if (error_ft_cd(cmd))
		return (1);
	getcwd(line, PATH_MAX);
	if (chdir(cmd[1]))
	{
		if(switch_old_pwd(data, line));
			return(1);
		if(switch_pwd(data, line, temp));
			return(1);
	}
	else
		return(1);
	return (0);
}

int	error_ft_cd(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 1)
		return (1);
	else
		return (0);
}

short	switch_old_pwd(t_data *data, char * line)
{
	t_env	*env;
	char	*temp;

	env = getenv("OLDPWD");
	temp = env->value;
	env->value = ft_strdup(line);
	if(!env->value)
	{
		env = getenv("PWD");
		chdir(env->value);
		free(temp);
		temp = NULL;
		return(1);
	}
	return (0);
}

short	switch_pwd(t_data *data, char * line, char *temp)
{
	t_env *env;

	getcwd(line, PATH_MAX);
	env = getenv("PWD");
	free(env->value);
	env->value = ft_strdup(line);
	if(!env->value)
	{
		env = getenv("OLDPWD");
		free(env->value);
		env->value = temp;
		chdir(temp);
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}
