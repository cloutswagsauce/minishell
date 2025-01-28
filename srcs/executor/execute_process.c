/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:20 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/28 20:37:56 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"


void	execute_process(t_com *commands, t_list **local_env, char **envp)
{
	
		/*if (commands->output_file)
		{
			printf("YESS");
			handle_redirect_out(commands);
		}*/
		if (!commands->is_builtin)
		{
			if (!fork())
				call_child_action(*commands, *local_env);
		}
		else
			execute_builtin_command(commands, local_env, envp);
		
	}

