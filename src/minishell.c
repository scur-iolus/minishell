/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/14 16:33:51 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_bad_characters(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i])
			// RAISE
		i++;
	}
}

void	remove_comment(char **line)
{
	size_t	len;
	char	*output;
	short	btwn_apo;

	len = 0;
	btwn_apo = 0;
	while ((*line)[len] && ((*line)[0] != '#'))
	{
		if ((*line)[len] == '\'')
			btwn_apo = !btwn_apo;
		if (len && (*line)[len] == '#' && (*line)[len - 1] == ' ' && !btwn_apo)
		{
			len--;
			break ;
		}
		len++;
	}
	output = calloc(len + 1, sizeof(char));
	while (len)
	{
		output[len - 1] = (*line)[len - 1];
		len--;
	}
	free(*line);
	(*line) = output;
}

void	reset_data(t_data *data)
{
	data->len_line = 0;
	data->exit_status = 0;
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
			remove_comment(&line);
		data.env_lst = init_env(env);
		printf("\n");
		line = convert_env_var(&data, line);
		printf("line vaut === %s$\n", line);

		// fonction de parsing
		/*
		if(!ft_strcmp("pwd", line))
			ft_pwd(&data);
		if(!ft_strcmp("env", line))
			ft_env(&data);

		//multipipe(structure principale);
		//fonction qui free tout avant la prochaine ligne de commande
		free(line);
		line = NULL;
		// l'exit(0) ne peut se faire que si l'utilisateur tape exit
	}
	printf("ERROR: no argument is required.\n");
	return (1);
}
