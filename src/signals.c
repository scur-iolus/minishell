/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:15:34 by llalba            #+#    #+#             */
/*   Updated: 2021/11/25 14:55:56 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_state = 1;

static void	sig_handler(int signo, siginfo_t *info, void *context)
{
	static char		c = 0;
	static short	bit = 8;
	pid_t			tmp_pid;
	static pid_t	client_pid = 0;
	short			done;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	else if (info->si_pid && client_pid != info->si_pid)
		return ;
	done = 0;
	tmp_pid = client_pid;
	bit--;
	c <<= 1;
	if (signo == SIGUSR1)
		c |= 1;
	if (bit <= 0 && c == '\0')
		done = 1;
	if (!next_char(&c, &bit, &client_pid))
		next_char(&c, &bit, &client_pid);
	if (done && kill(tmp_pid, SIGUSR2) < 0)
		;//ft_error(SENDER_NOT_FOUND);
	else if (kill(tmp_pid, SIGUSR1) < 0)
		;//ft_error(SENDER_NOT_FOUND);
}

/*
** Ctrl C -> SIGINT
** Ctrl \ -> SIGQUIT
*/

static void	signals_init(void)
{
	struct sigaction	action;
	sigset_t			empty_set;
	sigset_t			usr_set;

	sigemptyset(&empty_set);
	sigemptyset(&usr_set);
	sigaddset(&usr_set, SIGUSR1);
	sigaddset(&usr_set, SIGUSR2);
	action.sa_mask = empty_set;
	action.sa_flags = SA_RESTART | SA_SIGINFO;
	action.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
}
