/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:15:34 by llalba            #+#    #+#             */
/*   Updated: 2021/12/10 18:53:00 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** WIFEXITED return TRUE if the process returning status exited via the exit()
** system call. Then, WEXITSTATUS evaluates the exit code returned by the child.
**
** WIFSIGNALED evaluates to TRUE when the child process for which status was
** returned by the wait or waitpid function exited because it raised a signal
** that caused it to exit. Then, WTERMSIG evaluates the numeric value of the
** signal that was raised by the child process.
*/

void	update_status(pid_t this_pid)
{
	if (*g_status != 130)
	{
		if (WIFEXITED(this_pid))
		{
			*g_status = WEXITSTATUS(this_pid);
		}
		else if (WIFSIGNALED(this_pid))
		{
			*g_status = WTERMSIG(this_pid);
			if (*g_status != 131)
				*g_status += 128;
		}
	}
}

/*
** rl_replace_line: replaces the contents of rl_line_buffer with its argument
** rl_on_new_line: tell the update functions that we have moved onto a new line
** rl_redisplay: Replace the contents of rl_line_buffer with text
*/

static void	signal_handler(int signo)
{
	if (signo == SIGINT && *g_status != HAS_HEREDOC && *g_status != HAS_CHILD)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		*g_status = 130;
	}
	else if (signo == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (signo == SIGQUIT && *g_status == HAS_CHILD)
	{
		write(2, SIGQUIT_MSG, ft_strlen(SIGQUIT_MSG));
	}
	else if (signo == SIGQUIT \
	&& *g_status != HAS_CHILD && *g_status != HAS_HEREDOC)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

static void	signal_handler_child(int signo)
{
	if (signo == SIGINT)
		exit(130);
	else if (signo == SIGQUIT && *g_status == IS_HEREDOC)
		write(1, "\b\b  \b\b", 6);
	else if (signo == SIGQUIT && *g_status != IS_HEREDOC)
		exit(131);
}

void	signals_init(void)

{
	struct sigaction	action;
	sigset_t			empty_set;
	sigset_t			usr_set;

	sigemptyset(&empty_set);
	sigemptyset(&usr_set);
	sigaddset(&usr_set, SIGINT);
	sigaddset(&usr_set, SIGQUIT);
	action.sa_mask = empty_set;
	action.sa_flags = SA_RESTART;
	action.sa_handler = signal_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	signals_init_child(void)

{
	struct sigaction	action;
	sigset_t			empty_set;
	sigset_t			usr_set;

	sigemptyset(&empty_set);
	sigemptyset(&usr_set);
	sigaddset(&usr_set, SIGINT);
	sigaddset(&usr_set, SIGQUIT);
	action.sa_mask = empty_set;
	action.sa_flags = SA_RESTART;
	action.sa_handler = signal_handler_child;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}
