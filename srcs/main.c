/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/08 15:15:32 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		input = readline("mini$hell: ");
		if (*input)
		{
			parse_input(input, &command);
			if (!command.is_builtin)
			{
				if (!fork())
				{
					path_split_append(&command);
					add_history(input);
					exit(0);
				}
			}
			else
				execute_builtin_command(&command);
			free_command(&command);
			wait(0);
		}
	}
}
