/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/22 17:19:16 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_data(t_data *data)
{
	data->len_line = 0;
	data->exit_status = 0;
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
		init_data(&data);
		line = readline("Mishell c'est le Brésil>");
		if (ft_strlen(line) > 0)
			add_history(line);
		if (preliminary_checks(&line, &data, env));
		{
			build_cmd_list(&data, *line);
			printf("line vaut === %s$\n", line);
		}
		free(line);
		line = NULL;
	} // l'exit(0) ne peut se faire que si l'utilisateur tape exit
	write(2, TOO_MANY_ARG, ft_strlen(TOO_MANY_ARG));
	return (1);
}