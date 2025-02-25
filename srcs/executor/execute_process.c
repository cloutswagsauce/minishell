/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:20 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/25 20:16:29 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_absolute(t_com *command, t_data *data)
{
	char	*com;
	char	**args;

	com = command->argv[0];
	args = command->argv;
	if (!access(com, X_OK))
		execve(com, args, env_list_to_envp(data->envp));
}

void	store_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
	}
		
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	
}
void handle_child(t_com *cmd, t_data *data)
{
	if (cmd->delim)
			{
				if (handle_redirect_heredoc(cmd) != 0)
					exit(130);  // Exit if heredoc was interrupted
			}
			if (cmd->output_file)
				handle_redirect_out(cmd);
			if (cmd->argv[0][0] == '/')
				handle_absolute(cmd, data);
			call_child_action(*cmd, data);
	
}
void	execute_process(t_com *cmd, t_data *data)
{
	pid_t	pid;

	if (!cmd->is_builtin)
	{
		pid = fork();
		if (pid == 0)
			handle_child(cmd, data);
		else if (pid > 0)
		{
			waitpid(pid, &g_exit_status, 0);
			store_exit_status(g_exit_status);
			if (WIFEXITED(g_exit_status) && WEXITSTATUS(g_exit_status) == 130)
			{
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}
		}
	}
	else
		execute_builtin_command(cmd, data);
	//free_commands(cmd);
}
