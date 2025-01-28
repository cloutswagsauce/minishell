/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:18:05 by lfaria-m          #+#    #+#             */
/*   Updated: 2025/01/28 20:33:31 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../minishell.h"

int handle_redirect_out(t_com *cmd)
{
	printf("ft handle redirect was called");
	int fd;
	fd = open(cmd->output_file, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Errorrrr: ");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
