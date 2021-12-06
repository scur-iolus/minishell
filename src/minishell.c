/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/06 12:20:44 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long long	*g_exit_status;

static void	init_data(t_data *data, char **env)
{
	data->exit_status = 0;
	g_exit_status = &(data->exit_status);
	data->env = 0;
	data->path = 0;
	data->line = 0;
	data->cmd = 0;
	data->pipe.end = 0;
	data->pipe.nb_pipe = 0;
	data->pipe.cmd_nb = 0;
	data->pipe.cmd_len = 0;
	data->pipe.i = 0;
	data->env_lst = init_env(data, env); //FIXME : un leak lors du free de la list chainée ?
	update_var_shlvl(data);
}

static void	reset_data(t_data *data)
{
	if (data->env)
		ft_free_split(data->env);
	if (data->path)
		ft_free_split(data->path);
	if (data->line)
		free(data->line);
	if (data->cmd)
		ft_lstclear_cmd(data->cmd);
	free_pipe(data, &(data->pipe));
	data->line = 0;
	data->cmd = 0;
	data->env = list_to_env(data, data->env_lst);
	take_path(data);
}

static t_bool	is_too_long(char *line)
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

static t_bool	input_is_ok(t_data *data)
{
	char	*tmp;

	if (is_too_long(data->line))
		return (0);
	if (ft_strlen(data->line) > 0 && ft_strchr(data->line, (int) '#'))
		remove_comment(data);
	if (ft_strlen(data->line) > 0 && !even_nb_of_quote_marks(data->line))
		return (0);
	protect_with_backslash(data);
	data->line = convert_env_var(data);
	replace_backslash(data);
	tmp = data->line;
	data->line = ft_strtrim(data->line, " 	");
	free(tmp);
	if (!(data->line))
		err_free(MALLOC_ERROR, data, 0);
	if (!valid_start_end(data->line))
		return (0);
	deduplicate_spaces(data);
	space_before_after_chevron(data);
	if (too_many_chevrons_o_pipes(data) || invalid_suite(data))
		return (0);
	// printf("▫ data->line contient 🔹%s🔹\n", data->line); //FIXME
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	signals_init();
	init_data(&data, env);
	while (argc == 1)
	{
		reset_data(&data);
		data.line = readline("🌞 Mishell c'est le Brésil ▸ ");
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
