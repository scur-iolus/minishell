/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/15 18:50:14 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_data(t_data *data)// CHECKED
{
	data->line = 0;
	data->exit_status = 0;
	data->pipe = 0;
	data->cmd = 0;
	data->env_lst = 0;
}

/*
** free_data does not free(data) because it's on the stack (not on the heap).
*/

void	free_data(t_data *data)//CHECKED
{
	if (data->line)
		free(data->line);
	if (data->pipe)
		ft_lstclear_pipe(data->pipe);
	if (data->cmd)
		ft_lstclear_cmd(data->cmd);
	if (data->env_lst)
		ft_lstclear_env(data->env_lst);
	data->line = 0;
	data->pipe = 0;
	data->cmd = 0;
	data->env_lst = 0;
}

/*
** On the heap: line
*/

static short	line_too_long(char *line)
{
	unsigned long long	i;

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

static short	input_is_ok(t_data *data, char **env)//CHECKED
{
	char	*tmp;

	if (line_too_long(data->line));
		return (0);
	if (ft_strlen(data->line) > 0 && ft_strchr(data->line, (int) '#'))
		remove_comment(data);
	if (ft_strlen(data->line) > 0 && !even_nb_of_quote_marks(data->line))
		return (0);
	data->env_lst = init_env(data, env);
	data->line = convert_env_var(data);
	if (*(data->line) != '\0')
		remove_quotation_marks(data);
	tmp = data->line;
	data->line = ft_strtrim(data->line, " 	");
	if (!(data->line))
		err_free(MALLOC_ERROR, data, 0, 0);
	free(tmp);
	if (!valid_start_end(data->line))
		return (0);
	deduplicate_spaces(data);
	space_before_after_chevron(data);
	if (too_many_chevrons_o_pipes(data) || invalid_suite(data))
		return (0);
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
			parse_cmd_list(&data);
			// TODO : "utils_multipipe", parse_cmd, $? | $? | $. | $
		}
	}
	ft_error(TOO_MANY_ARG);
	return (1);
}
