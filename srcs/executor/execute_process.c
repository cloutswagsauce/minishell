/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:20 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/09 20:36:18 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

void handle_absolute(t_com *command, char **envp)
{
	char *com;
	char **args;
	
	com = command->argv[0];
	args = command->argv;
	if (!access(com, X_OK))
		execve(com, args, envp);
	
}

void	execute_process(t_com *cmd, t_list **local_env, char **envp)
{
		pid_t pid;
	
		if (!cmd->is_builtin)
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd->output_file || cmd->delim)
					handle_redirect_out(cmd);
				if (cmd->argv[0][0] == '/')
					handle_absolute(cmd, envp);
				call_child_action(*cmd, *local_env, envp);
			}
		}
		else
			execute_builtin_command(cmd, local_env, envp);
			
			
	}

