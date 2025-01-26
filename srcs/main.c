/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/24 18:53:23 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void	call_child_action(t_com command, t_list *local_env)
{
	path_split_append(&command, local_env);
	exit(0);
}

void	finish_execution(t_com *command, char *input)
{
	add_history(input);
	free_commands(command);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*local_env;
	t_com	*commands;
	
	local_env = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		rl_on_new_line();
		input = readline("mini$hell 🤖: ");
		if (*input)
		{
			commands = parse_input(input);
			if (commands && commands->has_outpipe)
				execute_pipeline(commands, &local_env, envp);
			else
				execute_process(commands, &local_env, envp);
			finish_execution(commands, input);
			wait(0);
		}
	}
}
