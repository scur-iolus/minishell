/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:15:34 by llalba            #+#    #+#             */
/*   Updated: 2021/12/06 12:24:10 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** https://github.com/louisnfr/minishell
** http://manpagesfr.free.fr/man/man2/wait.2.html
** https://github.com/iciamyplant/Minishell
** https://github.com/M0-san/minishell/blob/main/main/ft_signals.c
**
** https://www.youtube.com/watch?v=xVSPv-9x3gk
** https://putaindecode.io/articles/maitriser-les-redirections-shell/
** https://www.youtube.com/watch?v=EqndHT606Tw
** https://www.youtube.com/watch?v=uHH7nHkgZ4w
** https://brennan.io/2015/01/16/write-a-shell-in-c/
*/

// TODO cat pas cat, child pas child

/*
** WIFEXITED return TRUE if the process returning status exited via the exit()
** system call. Then, WEXITSTATUS evaluates the exit code returned by the child.
**
** WIFSIGNALED evaluates to TRUE when the child process for which status was
** returned by the wait or waitpid function exited because it raised a signal
** that caused it to exit. Then, WTERMSIG evaluates the numeric value of the
** signal that was raised by the child process.
*/

void	update_exit_status(pid_t this_pid)
{
	if (WIFEXITED(this_pid))
	{
		*g_exit_status = WEXITSTATUS(this_pid);
		printf("*g_exit_status : %lld\n", *g_exit_status); // FIXME
	}
	else if (WIFSIGNALED(this_pid))
	{
		*g_exit_status = WTERMSIG(this_pid);
		printf("*g_exit_status : %lld\n", *g_exit_status); // FIXME
		if (*g_exit_status != 131)
			*g_exit_status += 128;
	}
	fflush(stdout); // FIXME
}

/*
** rl_replace_line: replaces the contents of rl_line_buffer with its argument
** rl_on_new_line: tell the update functions that we have moved onto a new line
** rl_redisplay: Replace the contents of rl_line_buffer with text
*/

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		*g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		//ft_putstr_fd("\b\b  \b\b", 1);
		*g_exit_status = 131;
		ft_putstr_fd(SIGQUIT_MSG, 2);
	}
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
