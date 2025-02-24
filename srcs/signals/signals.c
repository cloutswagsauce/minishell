/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:27:53 by iduric            #+#    #+#             */
/*   Updated: 2025/02/17 18:14:10 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"


static void	handle_interactive(int sig)
{
	g_exit_status = sig + 128;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_non_interactive(int sig)
{
	g_exit_status = sig + 128;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}

void	signal_handler_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_interactive;
	sigaction(SIGINT, &act, NULL);
}

void	signal_handler_non_interactive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_non_interactive;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

//////////////////////HEREDOC SIGNAL HANDLING////////////////////////

static void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO); // Close stdin to force readline to return
		exit(130);
	}
}

void	signal_handler_heredoc(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_heredoc_signal;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN); // Ignore SIGQUIT in heredoc
}
