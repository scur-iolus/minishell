/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/15 16:52:38 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_comment(char *line)
{
	size_t	new_len;
	size_t	i;
	char	*output;

	new_len = 0;
	while (line[new_len] && line[new_len] != '#')
		new_len++;
	output = calloc(new_len + 1, sizeof(char));
	i = 0;
	while (i < new_len)
	{
		output[i] = line[i];
		i++;
	}
	free(line);
	line = output;
}

void	reset_data(t_data *data)
{
	data->len_line = 0;
	//free -----> data->pipe = ;
	//free -----> l_cmd = ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;

	(void)argv;

	while (argc == 1)
	{
		reset_data(&data);
		line = readline("Mishell c'est le Brésil>");
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strlen(line) > 0 && ft_strchr(line, (int) '#'))
			remove_comment(line);
		data.env_lst = init_env(env);
		line = convert_env_var(data.env_lst, line);
		// fonction de parsing

		// test de l'appel des fonctions
		if(!ft_strcmp("pwd", line))
			ft_pwd(&data);
		if(!ft_strcmp("env", line))
			ft_env(&data);
		// fonction qui fait la ou les commandes
		printf("line read --> %s\n", line);
		//multipipe(structure principale);
		free(line);
		line = NULL;
		// l'exit(0) ne peut se faire que si l'utilisateur tape exit
	}
	printf("ERROR: no argument is required.\n");
	return (1);
}
