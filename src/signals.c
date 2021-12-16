/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:15:34 by llalba            #+#    #+#             */
/*   Updated: 2021/12/16 18:16:59 by llalba           ###   ########.fr       */
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
			if (*g_status == SIGINT)
				*g_status += 128;
			else if (*g_status == SIGSEGV)
			{
				write(2, SIGSEGV_ERR, ft_strlen(SIGSEGV_ERR));
				*g_status = 139;
			}
			else if (*g_status == 15)
			{
				write(2, TERMINATED, ft_strlen(TERMINATED));
				*g_status = 143;
			}
		}
	}
}

/*
** rl_replace_line: replaces the contents of rl_line_buffer with its argument
** rl_on_new_line: tell the update functions that we have moved onto a new line
** rl_redisplay: Replace the contents of rl_line_buffer with text
*/

static void	sig_handler(int signo)
{
	if (signo == SIGINT && *g_status != HAS_HEREDOC && *g_status != HAS_CHILD)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		*g_status = SIGINT_PARENT;
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

static void	sig_handler_child(int signo)
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
	void	*ret;

	ret = 0;
	ret = signal(SIGSEGV, sig_handler);
	if (ret == SIG_ERR)
		write(2, SIG_FAILED, ft_strlen(SIG_FAILED));
	ret = signal(SIGQUIT, sig_handler);
	if (ret == SIG_ERR)
		write(2, SIG_FAILED, ft_strlen(SIG_FAILED));
	ret = signal(SIGINT, sig_handler);
	if (ret == SIG_ERR)
		write(2, SIG_FAILED, ft_strlen(SIG_FAILED));
}

void	signals_init_child(void)

{
	void	*ret;

	ret = 0;
	ret = signal(SIGINT, sig_handler_child);
	if (ret == SIG_ERR)
		write(2, SIG_FAILED, ft_strlen(SIG_FAILED));
	ret = signal(SIGQUIT, sig_handler_child);
	if (ret == SIG_ERR)
		write(2, SIG_FAILED, ft_strlen(SIG_FAILED));
}
