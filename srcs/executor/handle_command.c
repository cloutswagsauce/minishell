/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:31 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/09 20:40:17 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

void	execute_builtin_command(t_com *com, t_list **local_env, char **envp)
{
	int stdout_fd;
	int stdin_fd;
	
	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	
	command_has_variable(com, *local_env);
	if (com->delim)
		handle_redirect_heredoc(com);
	if (com->output_file)
		handle_redirect_out(com);
		
	if (!ft_strncmp(com->argv[0], "echo", ft_strlen(com->argv[0])))
		ft_echo(*com);
	else if (!ft_strncmp(com->argv[0], "env", ft_strlen(com->argv[0])))
		ft_env(envp, *local_env);
	else if (!ft_strncmp(com->argv[0], "pwd", ft_strlen(com->argv[0])))
		ft_pwd();
	else if (!ft_strncmp(com->argv[0], "cd", ft_strlen(com->argv[0])))
		ft_cd(*com);
	else if (!ft_strncmp(com->argv[0], "export", ft_strlen(com->argv[0])))
	{
		if (com->argv[1])
			ft_export(com->argv[1], local_env, envp, 0);
		else
			ft_export(com->argv[0], local_env, envp, 1);
	}
	else if (!ft_strncmp(com->argv[0], "exit", ft_strlen(com->argv[0])))
		ft_exit();
	else if (!ft_strncmp(com->argv[0], "unset", ft_strlen(com->argv[0])))
		ft_unset(com, local_env, envp);
	
	// Restore original file descriptors
	dup2(stdout_fd, STDOUT_FILENO);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdout_fd);
	close(stdin_fd);
}

void	handle_command(char *exec_path, t_com *command, t_list *local_env, char **envp)
{
	command_has_variable(command, local_env);
	if (execve(exec_path, command->argv, envp) == -1)
	{
		perror("execve failed");
		exit(126);
	}
}
