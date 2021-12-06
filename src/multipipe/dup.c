/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:21:50 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/03 18:01:08 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** on ouvre le infile quoi qu'il arrive...
** ou le here_doc
*/

void	open_infile_and_heredoc(t_cmd *cmd)
{
	if (cmd->infile)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	else if (cmd->heredoc)
		write(0, cmd->heredoc, ft_strlen(cmd->heredoc));
}

void	dup_outfile(t_cmd *cmd, t_pipe *pipe)
{
	dup2(cmd->outfile, STDOUT_FILENO);
	close(cmd->outfile);
}

void	command_failed_because_of_file_opening(t_data *data)
{
	free_everything(data, 0);
	exit(1);
}
