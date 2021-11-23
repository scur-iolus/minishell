/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:21:50 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/23 14:23:21 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_infile_and_heredoc(t_data *data, t_pipe *pipe, t_cmd *cmd)
{
		if (cmd->infile) // on ouvre le infile quoi qu'il arrive
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	else if (cmd->here_doc) // ou le here_doc
		ft_putstr_fd(cmd->here_doc, STDIN_FILENO);
}

void dup_outfile(t_cmd *cmd)
{
	dup2(cmd->outfile, STDOUT_FILENO);
	close(cmd->outfile);
	pipe->cmd_nb = 0;
	pipe->cmd_len = 0;
}
