/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/10 14:22:14 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_data(t_data *data)// CHECKED
{
	data->exit_status = 0;
	data->pipe = 0;
	data->cmd = 0;
	data->env_lst = 0;
}

/*
** Sur la heap: line
*/

static short	input_is_ok(t_data *data, char **env)
{
	char	*tmp;

	if (ft_strlen(data->line) > 0 && ft_strchr(data->line, (int) '#'))
		remove_comment(data);
	if (ft_strlen(data->line) > 0 && !even_nb_of_quote_marks(data->line))
		return (0);
	data->env_lst = init_env(data, env);
	data->line = convert_env_var(data);
	if (*(data->line) != '\0')
		remove_quotation_marks(line);
	tmp = data->line;
	data->line = ft_strtrim(data->line, " 	");
	free(tmp);
	if (!valid_start_end(data->line) || consecutive_chevrons_o_pipes(data->line))
		return (0);
	deduplicate_spaces(line);
	space_before_after_chevron(line);
	return (1);
}

/*
** exit(0) may only happen when the user enters 'exit'.
*/

int	main(int argc, char **argv, char **env)// CHECKED
{
	t_data	data;

	(void)argv;
	init_data(&data);
	while (argc == 1)
	{
		free_data(&data);
		data.line = readline("Mishell c'est le Brésil>");
		if (ft_strlen(data.line) > 0)
			add_history(data.line);
		if (input_is_ok(&data, env))
		{
			printf("data.line vaut === %s$\n", data.line);
			parse_cmd_list(&data, data.line);
		}
	}
	write(2, TOO_MANY_ARG, ft_strlen(TOO_MANY_ARG));
	return (1);
}
