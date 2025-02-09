/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/09 20:40:44 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

// i should create a data struct to contain localenv and envp cuz if not, it will be a fucking pain to pass everything i


void	call_child_action(t_com command, t_list *local_env, char **envp)
{
	path_split_append(&command, local_env, envp);
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
			else if (commands)
				execute_process(commands, &local_env, envp);
			wait(0);
			finish_execution(commands, input);
		}
	}
}
