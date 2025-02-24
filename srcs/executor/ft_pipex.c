/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:34:58 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/24 20:52:15 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_pipe_process(t_com *cmd, int fd_in, int *pipe_fd, t_data *data)
{
	if (cmd->has_inpipe)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->has_outpipe)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (cmd->output_file)
		handle_redirect_out(cmd);
	if (is_command_builtin(cmd))
	{
		execute_builtin_command(cmd, data);
		exit(0);
	}
	else
	{
		call_child_action(*cmd, data);
		exit(1);
	}
}

void	parent_pipe_process(t_com *cmd, int *fd_in, int *pipe_fd)
{
	if (cmd->has_inpipe)
		close(*fd_in);
	if (cmd->has_outpipe)
	{
		close(pipe_fd[1]);
		*fd_in = pipe_fd[0];
	}
}

void	check_if_failed(t_com *cmd, int *pipe_fd)
{
	if (cmd->has_outpipe)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe failed");
			exit(1);
		}
	}
}
void execute_pipeline(t_com *commands, t_data *data)
{
    int pipe_fd[2];
    int fd_in;
    pid_t pid;
    t_com *cmd;
    int status;

    fd_in = 0;
    cmd = commands;
    while (cmd)
    {
        check_if_failed(cmd, pipe_fd);
        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0)
            child_pipe_process(cmd, fd_in, pipe_fd, data);
        parent_pipe_process(cmd, &fd_in, pipe_fd);
        cmd = cmd->next;
    }
    while (waitpid(-1, &status, 0) > 0)
        store_exit_status(status);
   // free_commands(commands); // Free after execution
}
