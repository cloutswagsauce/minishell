/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:20 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/26 16:44:47 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"


void	execute_process(t_com *commands, t_list **local_env, char **envp)
{
	int	i;

	i = 0;
	while (commands)
	{
		if (!commands->is_builtin)
		{
			if (!fork())
				call_child_action(commands[i], *local_env);
		}
		else
			execute_builtin_command(&(commands[i]), local_env, envp);
		 commands = commands->next;
	}
}
