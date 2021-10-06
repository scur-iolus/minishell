/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:26:14 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/09/28 15:27:32 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	here_doc_filling(char **argv, t_data *data)
{
	char	*line;

	write(STDOUT_FILENO, "pipe heredoc> ", 14);
	while (get_next_line(0, &line, 0) != 0)
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			if (line)
				free(line);
			line = NULL;
			get_next_line(0, &line, 1);
			break ;
		}
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		write(data->here_doc, line, ft_strlen(line));
		write(data->here_doc, "\n", 1);
		if (line)
			free(line);
	}
}
