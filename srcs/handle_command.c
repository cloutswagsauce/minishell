/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:31 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/19 18:21:10 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void	execute_builtin_command(t_com *com, t_list **local_env, char **envp)
{
	command_has_variable(com, *local_env);

	if (!ft_strncmp(com->argv[0], "echo", ft_strlen(com->argv[0])))
		ft_echo(*com);
	else if (!ft_strncmp(com->argv[0], "env", ft_strlen(com->argv[0])))
		ft_env(envp, *local_env);
	else if (!ft_strncmp(com->argv[0], "pwd", ft_strlen(com->argv[0])))
		ft_pwd();
	else if (!ft_strncmp(com->argv[0], "cd", ft_strlen(com->argv[0])))
		ft_cd(*com);
	else if (!ft_strncmp(com->argv[0], "export", ft_strlen(com->argv[0])))
		ft_export(com->argv[1], local_env);
	else if (!ft_strncmp(com->argv[0], "exit", ft_strlen(com->argv[0])))
		ft_exit();
	else if (!ft_strncmp(com->argv[0], "unset", ft_strlen(com->argv[0])))
		ft_unset(com, local_env, envp);
}

void	handle_command(char *exec_path, t_com *command, t_list *local_env)
{
	
	command_has_variable(command, local_env);
	//command_has_pips()
	execv(exec_path, command->argv);
}
