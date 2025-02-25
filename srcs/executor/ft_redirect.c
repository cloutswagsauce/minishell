/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:18:05 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/25 19:26:34 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redirect_out(t_com *cmd)
{
	int	fd;
	if (!cmd)
	{
		printf("hi");
	}

	if (cmd->delim)
		return (handle_redirect_heredoc(cmd));
	if (cmd->append_output)
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	setup_heredoc(int pipe_fd[2], int *pid)
{
	pipe(pipe_fd);
	*pid = fork();
}

void	run_heredoc_child(int pipe_fd[2], t_com *cmd)
{
	char	*line;

	
	close(pipe_fd[0]);
	while (1)
	{
		signal_handler_heredoc();
		line = readline("heredoc> ");
		if (!line)
		{
			close(pipe_fd[1]);
			exit(0);
		}
		if (!ft_strncmp(line, cmd->delim, ft_strlen(cmd->delim))
			&& ft_strlen(line) == ft_strlen(cmd->delim))
		{
			free(line);
			close(pipe_fd[1]);
			exit(0);
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
}

int	finish_heredoc_parent(int pipe_fd[2], int pid)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(pipe_fd[0]);
		g_exit_status = 130;
		return (1);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}

int	handle_redirect_heredoc(t_com *cmd)
{
	int	pipe_fd[2];
	int	pid;

	setup_heredoc(pipe_fd, &pid);
	if (pid == 0)
		run_heredoc_child(pipe_fd, cmd);
	return (finish_heredoc_parent(pipe_fd, pid));
}
