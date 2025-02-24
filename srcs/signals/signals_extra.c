#include "../../minishell.h"

 void	handle_interactive(int sig)
{
	g_exit_status = sig + 128;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

 void	handle_non_interactive(int sig)
{
	g_exit_status = sig + 128;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

 void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}