/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/26 12:05:36 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_data(t_data *data, char **env)
{
	data->env = 0;
	data->path = 0;
	data->line = 0;
	data->exit_status = 0;
	data->cmd = 0;
	data->pipe.end = 0;
	data->pipe.nb_pipe = 0;
	data->pipe.cmd_nb = 0;
	data->pipe.cmd_len = 0;
	data->pipe.i = 0;
	data->env_lst = init_env(data, env);
}

/*
** Basically prints an error message on fd 2
*/

void	ft_error(char *str)//CHECKED
{
	write(2, EMOJI_X, ft_strlen(EMOJI_X));
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

/*
** On the heap: line
*/

static short	is_too_long(char *line)//CHECKED
{
	long long	i;

	i = 0;
	while (line[i])
	{
		if (i > 2147483646)
		{
			ft_error(LINE_TOO_LONG);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** On the heap: line
*/

static short	input_is_ok(t_data *data)//CHECKED
{
	char	*tmp;

	if (is_too_long(data->line))
		return (0);
	if (ft_strlen(data->line) > 0 && ft_strchr(data->line, (int) '#'))
		remove_comment(data);
	if (ft_strlen(data->line) > 0 && !even_nb_of_quote_marks(data->line))
		return (0);
	data->line = convert_env_var(data);
	if (*(data->line) != '\0')
		remove_quotation_marks(data);
	tmp = data->line;
	data->line = ft_strtrim(data->line, "  ");
	if (!(data->line))
		err_free(MALLOC_ERROR, data, 0);
	free(tmp);
	if (!valid_start_end(data->line))
		return (0);
	deduplicate_spaces(data);
	space_before_after_chevron(data);
	if (too_many_chevrons_o_pipes(data) || invalid_suite(data))
		return (0);
	//printf("✅ data->line contient 🔹%s🔹\n", data->line); //FIXME
	return (1);
}

/*
** exit(0) may only happen when the user enters 'exit'.
*/

int	main(int argc, char **argv, char **env)// CHECKED
{
	t_data	data;

	(void)argv;
	init_data(&data, env);
	while (argc == 1)
	{
		reset_data(&data);
		data.line = readline("🌞 Mishell c'est le Brésil> ");
		if (ft_strlen(data.line) > 0)
			add_history(data.line);
		if (input_is_ok(&data) && parse_cmd(&data) && data.cmd)
		{
			execute(&data);
		}
	}
	ft_error(TOO_MANY_ARG);
	return (1);
}

//FIXME : trouver pourquoi
