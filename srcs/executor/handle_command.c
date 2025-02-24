/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:31 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/24 12:20:59 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

int builtin_caller(t_com *com, t_data *data)
{
	if (com->delim)
		return (handle_redirect_heredoc(com));
	if (com->output_file)
		handle_redirect_out(com);
	if (!ft_strncmp(com->argv[0], "echo", ft_strlen(com->argv[0])))
		return (ft_echo(*com));
	else if (!ft_strncmp(com->argv[0], "env", ft_strlen(com->argv[0])))
		return (ft_env(data));
	else if (!ft_strncmp(com->argv[0], "pwd", ft_strlen(com->argv[0])))
		return (ft_pwd());
	else if (!ft_strncmp(com->argv[0], "cd", ft_strlen(com->argv[0])))
		return (ft_cd(*com));
	else if (!ft_strncmp(com->argv[0], "export", ft_strlen(com->argv[0])))
	{
		if (com->argv[1])
			return (ft_export(com->argv, com, data,  0));
		else
			return (ft_export(com->argv,com, data, 1));
	}
	else if (!ft_strncmp(com->argv[0], "exit", ft_strlen(com->argv[0])))
		return (ft_exit(com, data));
	else if (!ft_strncmp(com->argv[0], "unset", ft_strlen(com->argv[0])))
		return (ft_unset(com, data));
	return (127);
}

void	execute_builtin_command(t_com *com, t_data *data)
{
	int	stdout_fd;
	int	stdin_fd;

	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	command_has_variable(com, data->local_env);
	store_exit_status(builtin_caller(com, data));
	dup2(stdout_fd, STDOUT_FILENO);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdout_fd);
	close(stdin_fd);
}

void handle_command(char *exec_path, t_com *command, t_data *data)
{
    command_has_variable(command, data->local_env);
    if (execve(exec_path, command->argv, env_list_to_envp(data->envp)) == -1)
    {
        perror("execve failed");
        exit(126);
    }
}
