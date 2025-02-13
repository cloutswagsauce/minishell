/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:18:05 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/13 11:21:39 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

int	handle_redirect_out(t_com *cmd)
{
	int	fd;

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

int	handle_redirect_heredoc(t_com *cmd)
{
	int		pipe_fd[2];
	char	*line;
	int		pid;
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (1)
		{
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
	waitpid(pid, &status, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}
