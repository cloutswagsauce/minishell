/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:31 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/04 20:16:13 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

int	is_command_builtin(char *command)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(command, builtin_list[i], ft_strlen(command)))
			return (1);
		i++;
	}
	return (0);
}

void	execute_builtin_command(char **command)
{
	// to be implemented
	printf("%s\n", *command);
}

void	handle_command(char *exec_path, t_com command)
{
	if (is_command_builtin(command.argv[0]))
	{
		command.is_builtin = 1; // not sure if we'll need this later or not
		execute_builtin_command(command.argv);
	}
	else
		execv(exec_path, command.argv);
}
/*
int	exec_command(char *exec_path, t_com command)
{
   execv(exec_path, command.argv);
} */
