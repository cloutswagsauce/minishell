/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/13 13:19:00 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

const char	*g_builtin_list[] =
{
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit",
	NULL
};

void call_child_action(t_com command, t_list *local_env)
{
	path_split_append(&command, local_env);
	exit(0);
	
}

void finish_execution(t_com command, char *input)
{
	add_history(input);
	free_command(&command);
	
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_com	command;
	t_list	*local_env;

	local_env = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		rl_on_new_line();
		input = readline("mini$hell: ");
		if (*input)
		{
			parse_input(input, &command);
			if (!command.is_builtin)
			{
				if (!fork())
					call_child_action(command, local_env);
			}
			else
				execute_builtin_command(&command, &local_env, envp);
			finish_execution(command, input);
			wait(0);
		}
	}
}
