/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:20 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/14 20:52:46 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

void	handle_absolute(t_com *command, t_data *data)
{
	char	*com;
	char	**args;

	com = command->argv[0];
	args = command->argv;
	if (!access(com, X_OK))
		execve(com, args, data->envp);
}

void	store_exit_status(int nb)
{
	(void)nb;
}

void	execute_process(t_com *cmd, t_data *data)
{
	pid_t	pid;

	if (!cmd->is_builtin)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->delim)
				handle_redirect_heredoc(cmd);
			if (cmd->output_file)
				handle_redirect_out(cmd);
			if (cmd->argv[0][0] == '/')
				handle_absolute(cmd, data);
			call_child_action(*cmd, data);
		}
	}
	else
	{
		printf("do i think this is builtin : %d\n", cmd->is_builtin);
		execute_builtin_command(cmd, data);
	}
		
}
