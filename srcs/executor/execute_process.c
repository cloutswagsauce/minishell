/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:20 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/26 12:18:21 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

void execute_pipeline(t_com *commands, t_list **local_env, char **envp)
{
	int pipe_fd[2];
	int fd_in = 0;
	pid_t pid;
	t_com *cmd = commands;

	while (cmd)
	{
		if (cmd->has_outpipe)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe failed");
				exit(1);
			}
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		else if (pid == 0)
		{
			if (cmd->has_inpipe)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (cmd->has_outpipe)
			{
				dup2(pipe_fd[1], STDERR_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			if (is_command_builtin(cmd))
				execute_builtin_command(cmd, local_env, envp);
			else
				execvp(cmd->argv[0], cmd->argv);
			//perror("exec failed");
			exit(1);	
		}
		if (cmd->has_inpipe)
			close(fd_in);
		if (cmd->has_outpipe)
		{
			close(pipe_fd[1]);
			fd_in = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
}

void	execute_process(t_com *commands, t_list **local_env, char **envp)
{
	int	i;

	i = 0;
	while (commands)
	{
		if (!commands[i].is_builtin)
		{
			if (!fork())
				call_child_action(commands[i], *local_env);
		}
		else
			execute_builtin_command(&(commands[i]), local_env, envp);
		 commands = commands->next;
	}
}
