/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:31 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/04 16:35:28 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_command(char *exec_path, t_com command)
{
	if (command.argv[0])
		execv(exec_path, command.argv);
	// if command is built in, set is built in attribute to true

}
 /*
int exec_command(char *exec_path, t_com command)
{
	execv(exec_path, command.argv);
} */
