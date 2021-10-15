/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:32:59 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/15 16:50:28 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(t_data *data, char *line)
{
	char line[PATH_MAX];
	char *temp;

	getcwd(line, PATH_MAX);
	data->exit_status = 0;
	if (chdir(Nom du dir dans l_cmd))
	{
		if(!(temp = switch_old_pwd(data, line)));
		{
			data->exit_status = 1;
			return ;
		}
		if(!switch_pwd(data, line, temp));
		{
			data->exit_status = 1;
			return ;
		}
	}
	else
		data->exit_status = 1;
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
		return(temp);
	}
	return (temp);
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
		return (0);
	}
	free(temp);
	return (1);
}
