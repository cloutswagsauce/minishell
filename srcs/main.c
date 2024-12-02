/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:24:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/02 16:42:11 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(void)
{
	char *input;
	pid_t pid;
	t_com command;

	while (1)
	{
		input = readline("mini$hell: ");
		if (*input)
		{
			command = parse_input(input);
			add_history(input);
			pid = fork();
			if (!pid)
			{
				execve("/bin/ls", command.argv, 0);
				exit(0);
			}
			wait(0);
		}
	}
}