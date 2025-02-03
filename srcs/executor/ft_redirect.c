/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:18:05 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/02/03 20:23:28 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

int handle_redirect_out(t_com *cmd)
{
	int fd;
	if (cmd->append_output)
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(cmd->output_file, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error: ");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	return (0);
}
