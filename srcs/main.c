/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/14 16:16:20 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"



void	call_child_action(t_com command, t_data *data)
{
	path_split_append(&command, data);
	exit(0);
}

void	finish_execution(t_com *command, char *input)
{
	add_history(input);
	free_commands(command);
}

int init_data(t_data **data, char **envp, t_list *local_env)
{
	*data = malloc(sizeof(t_data));
	(*data)->envp = envp;
	(*data)->local_env = local_env;
	return (0);
	
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*local_env;
	t_com	*commands;
	t_data	*data;

	(void)argc;
	(void)argv;
	local_env = 0;
	data = 0;
	init_data(&data, envp, local_env);
	while (1)
	{
		rl_on_new_line();
		input = readline("mini$hell 🤖: ");
		if (*input)
		{
			commands = parse_input(input);
			if (commands && commands->has_outpipe)
				execute_pipeline(commands, data);
			else if (commands)
				execute_process(commands, data);
			wait(0);
			finish_execution(commands, input);
		}
	}
}
