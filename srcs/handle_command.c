/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:31 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/11 17:34:25 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void	execute_builtin_command(t_com *command)
{
	if (!ft_strncmp(command->argv[0], "echo", ft_strlen(command->argv[0])))
		ft_echo(*command);
	else if (!ft_strncmp(command->argv[0], "env", ft_strlen(command->argv[0])))
		ft_env(command->argv[1]);
	else if (!ft_strncmp(command->argv[0], "pwd", ft_strlen(command->argv[0])))
		ft_pwd();
	else if (!ft_strncmp(command->argv[0], "cd", ft_strlen(command->argv[0])))
		ft_cd(*command);
	else if (!ft_strncmp(command->argv[0], "history", ft_strlen(command->argv[0])))
		ft_cd(*command);
	else if (!ft_strncmp(command->argv[0], "cd", ft_strlen(command->argv[0])))
		ft_cd(*command);
	else if (!ft_strncmp(command->argv[0], "cd", ft_strlen(command->argv[0])))
		ft_cd(*command);
}

void	handle_command(char *exec_path, t_com *command)
{
		execv(exec_path, command->argv);
}
