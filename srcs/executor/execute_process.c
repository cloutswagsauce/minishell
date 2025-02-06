/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:20 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/06 13:55:42 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"


void	execute_process(t_com *cmd, t_list **local_env, char **envp)
{
		pid_t pid;
	
		if (!cmd->is_builtin)
		{
			printf("command not builtin");
			pid = fork();
			if (pid == 0)
			{
				if (cmd->output_file)
					handle_redirect_out(cmd);
				if (cmd->delim)
				{
					printf("HEREDOC MODE BITCHH!!");
					handle_redirect_out(cmd);
				}
					
				call_child_action(*cmd, *local_env);
			}
		}
		else
		{
			printf("command builtin");
			execute_builtin_command(cmd, local_env, envp);
		}
			
	}

