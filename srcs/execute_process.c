/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:20 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/20 16:14:07 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void	execute_process(t_com *commands, t_list **local_env, char **envp)
{
	int	i;

	i = 0;
	while (i < commands[0].total_commands)
	{
		printf("is standalone? : %d \n", commands[0].is_stand_alone);
		printf("number of commands: %d\n", commands[0].total_commands);
		if (!commands[i].is_builtin || !commands[0].is_stand_alone)
		{
			if (!fork())
				call_child_action(commands[i], *local_env);
		}
		else
		{
			printf("is standalone? : %d", commands[i].is_stand_alone);
			execute_builtin_command(&(commands[i]), local_env, envp);
		}
		 i++;
	}
}
