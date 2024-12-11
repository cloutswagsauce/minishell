/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:18:42 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/11 17:36:55 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void	ft_cd(t_com command)
{
	if (!command.argv[1])
		chdir("/");
	else if (command.argv[1])
		if (chdir(command.argv[1]))
			perror("not a valid directory");
}