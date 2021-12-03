/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:31:57 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/03 14:48:56 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_add_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	if (!(*alst))
		*alst = new;
	else
	{
		last = *alst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_cmd	*ft_lstnew_cmd(char *raw)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->raw = raw;
	new->ok = TRUE;
	new->split = NULL;
	new->cmd_path = NULL;
	new->cmd = NULL;
	new->infile = 0;
	new->outfile = 0;
	new->heredoc = NULL;
	new->next = NULL;
	return (new);
}

static void	close_fd(t_cmd *head)
{
	t_bool	fail;

	fail = 0;
	if (head->infile)
		fail -= close(head->infile);
	if (head->outfile)
		fail -= close(head->outfile);
	if (fail)
		ft_error(CLOSE_FAILED);
}

void	ft_lstclear_cmd(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->raw)
			free(head->raw);
		if (head->split)
			ft_free_split(head->split);
		if (head->heredoc)
			free(head->heredoc);
		if (head->cmd)
			ft_free_split(head->cmd);
		if (head->cmd_path)
			free(head->cmd_path);
		free(head);
		head = tmp;
	}
}

int	ft_lstsize(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
