/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:18:05 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/08 16:30:55 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_redirect_out(t_com *cmd)
{
	int fd;

	if (cmd->delim)
		return (handle_redirect_heredoc(cmd));
	if (cmd->append_output)
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(cmd->output_file, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error: ");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	return (0);
}

int handle_redirect_heredoc(t_com *cmd)
{
	int pipe_fd[2];
	char *line;
	int pid;

	pipe(pipe_fd);
	if (!(pid = fork()))
	{
		while (1)
		{
			close(pipe_fd[0]);
			line = readline("heredoc> ");
			if (!ft_strncmp(line, cmd->delim, ft_strlen(line)))
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
	wait(0);
	close(pipe_fd[1]);
	cmd->input_fd = pipe_fd[0];
	dup2(cmd->input_fd, STDIN_FILENO);
	return (0);
	
}


