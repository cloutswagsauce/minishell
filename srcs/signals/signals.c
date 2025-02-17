/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:27:53 by iduric            #+#    #+#             */
/*   Updated: 2025/02/17 10:17:24 by lfaria-m         ###   ########.fr       */
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
		exit(130); // Exit heredoc process immediately
	}
}

void	signal_handler_heredoc(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_heredoc_signal;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL); // Optional: Ignore SIGQUIT
}
