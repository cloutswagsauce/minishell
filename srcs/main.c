/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/11 17:50:54 by lfaria-m         ###   ########.fr       */
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

int	main(void)
{
	char	*input;
	t_com	command;

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
				{
					path_split_append(&command);
					exit(0);
				}
			}
			else
				execute_builtin_command(&command);
			add_history(input);
			free_command(&command);
			wait(0);
		}
	}
}
