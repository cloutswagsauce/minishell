/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:31 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/08 16:18:12 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin_command(t_com *command)
{
	printf("%s\n", command->argv[0]);
}

void	handle_command(char *exec_path, t_com *command)
{
		execv(exec_path, command->argv);
	
}
